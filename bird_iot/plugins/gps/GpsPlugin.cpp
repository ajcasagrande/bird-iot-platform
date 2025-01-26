#include "GpsPlugin.h"
#if CONFIG_ENABLE_GPS_PLUGIN

#include <HardwareSerial.h>

#if CONFIG_ENABLE_TFT_DISPLAY
DisplayManager GpsDisplay;
#include "tft_includes.h"
#endif

#define MIN_SAT_MAX_SPEED (8)

#ifndef CR
#define CR ((char)13)
#endif
#ifndef LF
#define LF ((char)10)
#endif

#define UBX_SYNC1 (0xB5)
#define UBX_SYNC2 (0x62)
#define SEND_UBX(ubx) sendUBX(ubx, sizeof(ubx))

static const char* TAG = "GPS";

// Format lower nybble of value as HEX and returns character.

static char formatHex(uint8_t val) {
  val &= 0x0F;
  return (val >= 10) ? ((val - 10) + 'A') : (val + '0');
}

static void send_trailer(Stream *device, uint8_t crc) {
  device->print('*');

  char hexDigit = formatHex(crc>>4);
  device->print(hexDigit);

  hexDigit = formatHex(crc);
  device->print(hexDigit);

  device->print(CR);
  device->print(LF);

}

void send_P(Stream *device, const __FlashStringHelper *msg) {
  if (msg) {
    const char *ptr = (const char *)msg;
    char  chr = pgm_read_byte(ptr++);

    device->print('$');
    if (chr == '$')
      chr = pgm_read_byte(ptr++);
    uint8_t sent_trailer = 0;
    uint8_t crc          = 0;
    while (chr) {
      if ((chr == '*') || (sent_trailer > 0)) {
        sent_trailer++;
      } else {
        crc ^= chr;
      }
      device->print(chr);

      chr = pgm_read_byte(ptr++);
    }

    if (!sent_trailer) {
      send_trailer(device, crc);
    }
  }

}

void _poll(GpsPlugin* plugin) {
  plugin->poll();
}

void _render(GpsPlugin *plugin) {
  plugin->render();
}

GpsPlugin::GpsPlugin()
    : IotPlugin("Gps Plugin")
#if CONFIG_ENABLE_TFT_DISPLAY
      , speedFrame(this), maxSpeedOverlay(this),
      satOverlay(this),
      latOverlay(this), lonOverlay(this)
#endif
      {
  pollTask = new Task<GpsPlugin>("GPS Serial", this, _poll);
  refreshTask = new Task<GpsPlugin>("GPS Refresh", this, _render);

#if CONFIG_ENABLE_TFT_DISPLAY
  GpsDisplay.registerFrame(&speedFrame);
  GpsDisplay.registerOverlay(&maxSpeedOverlay);
  GpsDisplay.registerOverlay(&satOverlay);
  GpsDisplay.registerOverlay(&latOverlay);
  GpsDisplay.registerOverlay(&lonOverlay);
#endif
}

void GpsPlugin::sendUBX(const unsigned char *progmemBytes, size_t len) {
  gpsSerial->write(UBX_SYNC1);
  gpsSerial->write(UBX_SYNC2);

  // CHECKSUMS
  uint8_t a = 0, b = 0;
  while (len-- > 0) {
    uint8_t c = pgm_read_byte(progmemBytes++);
    a += c;
    b += a;
    gpsSerial->write(c);
  }

  gpsSerial->write(a); // CHECKSUM A
  gpsSerial->write(b); // CHECKSUM B
}

void GpsPlugin::setUpdateRate() {
#if CONFIG_GPS_RATE_1_HZ
  SEND_UBX(ubxRate1Hz);
#elif CONFIG_GPS_RATE_5_HZ
  SEND_UBX(ubxRate5Hz);
#elif CONFIG_GPS_RATE_10_HZ
  SEND_UBX(ubxRate10Hz);
#elif CONFIG_GPS_RATE_16_HZ
  SEND_UBX(ubxRate16Hz);
#else
#error "invalid value specified for CONFIG_GPS_UPDATE_RATE_HZ. valid values are [1, 5, 10, 16]"
#endif
}

bool GpsPlugin::setup() {
  LOGI(TAG, "setting up GPS");
  if (App.profile.gpsUartNumber < 1 || App.profile.gpsUartNumber > 2) {
    LOGE(TAG, "invalid gps uart specified. valid values are 1 or 2. specified: " << App.profile.gpsUartNumber);
    return false;
  }
  // remember, the gpsRxPin is the one we SEND data over to be Received by the GPS
  if (isPin(App.profile.gpsTxPin) && !GPIO_IS_VALID_OUTPUT_GPIO(App.profile.gpsRxPin)) {
    LOGE(TAG, "invalid gps pins specified");
  }

  gpsSerial = new HardwareSerial(App.profile.gpsUartNumber);
  // NOTE: GPS RX and TX pins are swapped because the profile is setup based on the labelling of the GPS module
  // which is labelled TX for the pin that sends data from the GPS to the MCU, whereas that is actually
  // the RX pin for the MCU because that is the pin the MCU is receiving data on
  gpsSerial->begin(9600, SERIAL_8N1, App.profile.gpsTxPin, App.profile.gpsRxPin);
  LOGD(TAG, "after setup GPS serial");

  setUpdateRate();

  return pollTask->configure(10, _2k, HIGH_PRIORITY, CORE_0, true, false) &&
         refreshTask->configure(33, _1p25, LOW_PRIORITY, tskNO_AFFINITY, true, false);
}

bool GpsPlugin::start() {
#if CONFIG_ENABLE_TFT_DISPLAY
  TFTDisplay.setManager(&GpsDisplay);
#endif
  return pollTask->start()
         && refreshTask->start();
}

void GpsPlugin::poll() {
  while (gpsSerial->available() > 0) {
    gps.encode(char(gpsSerial->read()));
  }
}

#if CONFIG_ENABLE_TFT_DISPLAY
SpeedFrame::SpeedFrame(GpsPlugin *plugin)
    : StringDrawable(plugin, 10, &DejaVu_Sans_64, TFT_CYAN) {
}
void SpeedFrame::updateCurrent() {
  double mph = 0;
  if (plugin->gps.speed.age() <= 1000) {
    mph = plugin->speeds.mean();
    snprintf(current, strLength, "%.1f", mph);
  } else {
    strcpy(current, "--");
  }

  if (mph > plugin->maxSpeed && plugin->gps.satellites.value() >= MIN_SAT_MAX_SPEED) {
    plugin->maxSpeed = mph;
    plugin->maxSpeedOverlay.setDirty(true);
  }
}
StringRenderInfo SpeedFrame::getRenderInfo(TFT_eSPI *img, DisplayUI& ui, int16_t textWidth) {
  return StringRenderInfo(ui.centerX - textWidth/2, (ui.height / 2) - (img->glyph_ab / 2), true); // NOLINT(modernize-return-braced-init-list)
}

MaxSpeedOverlay::MaxSpeedOverlay(GpsPlugin *plugin)
    : StringDrawable(plugin, 10, &DejaVu_Sans_36, TFT_PINK) {
}
void MaxSpeedOverlay::updateCurrent() {
  snprintf(current, strLength, "%.1f", plugin->maxSpeed);
}
StringRenderInfo MaxSpeedOverlay::getRenderInfo(TFT_eSPI *img, DisplayUI& ui, int16_t textWidth) {
  return StringRenderInfo(ui.width - textWidth, 0); // NOLINT(modernize-return-braced-init-list)
}

SatelliteOverlay::SatelliteOverlay(GpsPlugin *plugin)
    : StringDrawable(plugin, 4, &DejaVu_Sans_36, TFT_PINK) {
}
void SatelliteOverlay::updateCurrent() {
  snprintf(current, strLength, "%-2u", plugin->gps.satellites.value());
}
StringRenderInfo SatelliteOverlay::getRenderInfo(TFT_eSPI *img, DisplayUI& ui, int16_t textWidth) {
  return StringRenderInfo(ui.width - textWidth, 0); // NOLINT(modernize-return-braced-init-list)
}

LatOverlay::LatOverlay(GpsPlugin *plugin)
    : StringDrawable(plugin, 4, &DejaVu_Sans_16, TFT_GREEN) {
}
void LatOverlay::updateCurrent() {
  snprintf(current, strLength, "Lat: %11f", plugin->gps.location.lat());
}
StringRenderInfo LatOverlay::getRenderInfo(TFT_eSPI *img, DisplayUI& ui, int16_t textWidth) {
  return StringRenderInfo(0, ui.height - (img->glyph_ab * 2.1)); // NOLINT(modernize-return-braced-init-list)
}

LonOverlay::LonOverlay(GpsPlugin *plugin)
: StringDrawable(plugin, 4, &DejaVu_Sans_16, TFT_GREEN) {
}
void LonOverlay::updateCurrent() {
  snprintf(current, strLength, "Lon: %11f", plugin->gps.location.lng());
}
StringRenderInfo LonOverlay::getRenderInfo(TFT_eSPI *img, DisplayUI& ui, int16_t textWidth) {
  return StringRenderInfo(0, ui.height - img->glyph_ab); // NOLINT(modernize-return-braced-init-list)
}
#endif

void GpsPlugin::render() {
  if (gps.speed.isUpdated()) {
#if CONFIG_PRINT_GPS_VALUES
    LOGD(TAG, "Speed: " << gps.speed.mph() << " mph");
#endif
    speeds.add(gps.speed.mph());
#if CONFIG_ENABLE_TFT_DISPLAY
    speedFrame.setDirty(true);
  } else if (gps.speed.age() > 1000) {
    speedFrame.setDirty(true);
#endif
  }

  if (gps.location.isUpdated()) {
#if CONFIG_PRINT_GPS_VALUES
    LOGD(TAG, "lat: " << gps.location.lat() << ", long: " << gps.location.lng());
#endif
#if CONFIG_ENABLE_TFT_DISPLAY
    latOverlay.setDirty(true);
    lonOverlay.setDirty(true);
  }

  if (gps.satellites.isUpdated()) {
    satOverlay.setDirty(true);
#endif
  }
}

bool GpsPlugin::handleCommand(const std::string& cmd) {
  if (cmd == "gps" || cmd == "loc" || cmd == "location") {
    PUTLN("    Max Speed | " << maxSpeed << " mph");
    PUTLN("Current Speed | " << gps.speed.mph() << " mph " DIM_STYLE "(" << gps.speed.age() << " ms ago)");
    PUTLN("          Lat | " << gps.location.lat());
    PUTLN("         Long | " << gps.location.lng()  << DIM_STYLE " (" << gps.location.age() << " ms ago)");
    PUTLN("   Satellites | " << gps.satellites.value() << DIM_STYLE " (" << gps.satellites.age() << " ms ago)");
  } else {
    return false;
  }

  return true;
}

#endif // CONFIG_ENABLE_GPS_PLUGIN
