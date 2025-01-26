#include "QMC5883LCompass.h"

#if CONFIG_ENABLE_QMC5883L_COMPASS_SENSOR

#include "GpsPlugin.h"
#include "i2cDriver.h"

static const char* TAG = "Compass";

#define N_NE  (22.5)
#define E_NE  (67.5)
#define E_SE  (112.5)
#define S_SE  (157.5)
#define S_SW  (202.5)
#define W_SW  (247.5)
#define W_NW  (292.5)
#define N_NW  (337.5)

const char* headingName(uint16_t h) {
  if (h < N_NE || h >= N_NW)  return  "N"; // North is both 0 and 360
  if (h >= N_NE && h < E_NE)  return "NE";
  if (h >= E_NE && h < E_SE)  return  "E";
  if (h >= E_SE && h < S_SE)  return "SE";
  if (h >= S_SE && h < S_SW)  return  "S";
  if (h >= S_SW && h < W_SW)  return "SW";
  if (h >= W_SW && h < W_NW)  return  "W";
  if (h >= W_NW && h < N_NW)  return "NW";

  // should never reach here
  return "";
}

QMC5883LCompass::QMC5883LCompass()
    : BaseSensor("QMC5883L Compass", "Compass")
#if CONFIG_ENABLE_TFT_DISPLAY
    , compassOverlay(this)
#endif
    {
}

bool QMC5883LCompass::setup() {
  TRY_LOCK(i2cDriver,
    compass.init();
  , return false;);

#if CONFIG_ENABLE_GPS_PLUGIN
#if CONFIG_ENABLE_TFT_DISPLAY
  GpsDisplay.registerOverlay(&compassOverlay);
#endif
#endif

  return pollTask->configure(CONFIG_QMC5883L_COMPASS_SENSOR_POLL_INTERVAL, _1p75, MEDIUM_PRIORITY)
          && publishTask->configure(CONFIG_QMC5883L_COMPASS_SENSOR_PUBLISH_INTERVAL, _1p75, MEDIUM_PRIORITY);
}

void QMC5883LCompass::poll() {
  static uint16_t prev = 0;

  uint16_t h = 0;
  TRY_LOCK(i2cDriver,
    if (compass.ready()) {
      h = (uint16_t) compass.readHeading();
    }
  , return;);

  if (h == 0) { return; }
  if (h != prev) {
    const char *dir = headingName(h);
#if CONFIG_ENABLE_TFT_DISPLAY
    compassOverlay.setCurrent(dir);
#endif
    LOGD(TAG, "heading: " << h << "° (" << dir << ")");
  }
  prev = h;
}

void QMC5883LCompass::publishData() {
  // todo
}

#if CONFIG_ENABLE_TFT_DISPLAY
CompassOverlay::CompassOverlay(QMC5883LCompass *plugin)
    : StringDrawable(plugin, 3, &DejaVu_Sans_42, TFT_RED) {
}
StringRenderInfo CompassOverlay::getRenderInfo(TFT_eSPI *img, DisplayUI& ui, int16_t textWidth) {
  return StringRenderInfo(ui.width - textWidth, ui.height - img->glyph_ab); // NOLINT(modernize-return-braced-init-list)
}

#endif

//  void QMC5883LCompass::onWifiConnected() { }
//  void QMC5883LCompass::onWifiDisconnected() { }
//  void QMC5883LCompass::onMqttConnected() { }
//  void QMC5883LCompass::onMqttDisconnected() { }
//  bool QMC5883LCompass::handleMqttMessage(const char *topic, int id, const char *cmd, const JsonDocument& json) {
//   return false; // false means not handled 
// }
//  bool QMC5883LCompass::handleCommand(const std::string& cmd) {
//   return false; // false means not handled 
// }
#if ENABLE_I2C_OLED_DISPLAY_PLUGIN
//  void QMC5883LCompass::addFramesAndOverlays() { }
#endif

#endif // CONFIG_ENABLE_QMC5883L_COMPASS_SENSOR
