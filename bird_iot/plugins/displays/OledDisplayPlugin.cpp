#include "OledDisplayPlugin.h"

#if CONFIG_ENABLE_I2C_OLED_DISPLAY_PLUGIN

#include <OLEDDisplayFonts.h>

#include "I2CDriver.h"
#include "include/common.h"

#include "oled_fonts.h"
#include "oled_icons.h"

static void _execute(OledDisplayPlugin *plugin) {
  plugin->execute();
}

OledDisplayPlugin::OledDisplayPlugin(uint8_t address) : IotPlugin("OledDisplay Plugin"), address(address) {
  TRY_LOCK(i2cDriver,
    _display = new SSD1306Wire(address, App.profile.sda, App.profile.scl);
    ui = new OLEDDisplayUi(_display);
    task = new Task<OledDisplayPlugin>("OLED", this, _execute);
  i2cDriver.unlock();
}

void msOverlay(OLEDDisplay *display, OLEDDisplayUiState* state) {
  display->setTextAlignment(TEXT_ALIGN_RIGHT);
  display->setFont(ArialMT_Plain_10);
  display->drawString(display->getWidth(), display->getHeight() - 10, String(millis()));
}

void timeOverlay(OLEDDisplay *display, OLEDDisplayUiState* state) {
  display->setTextAlignment(TEXT_ALIGN_RIGHT);
  display->setFont(ArialMT_Plain_10);

  time_t now = time(nullptr);
  tm timeinfo{};
  gmtime_r(&now, &timeinfo);
  display->drawString(display->getWidth(), display->getHeight() - 10, String(asctime(&timeinfo)));
}

void heapOverlay(OLEDDisplay *display, OLEDDisplayUiState* state) {
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->setFont(ArialMT_Plain_10);
  display->drawString(0, display->getHeight() - 10, String(ESP.getFreeHeap()));
}

void deviceIdOverlay(OLEDDisplay *display, OLEDDisplayUiState* state) {
  display->setTextAlignment(TEXT_ALIGN_RIGHT);
  display->setFont(ArialMT_Plain_10);
  display->drawString(display->getWidth(), display->getHeight() - 10, String(deviceId()));
}

void rssiOverlay(OLEDDisplay *display, OLEDDisplayUiState* state) {
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->setFont(ArialMT_Plain_10);
  display->drawString(0, display->getHeight() - 10, String(WiFi.RSSI()));
}

void OledDisplayPlugin::drawProgress(uint8_t percent, String strTop, String strBottom) {
  TRY_LOCK(i2cDriver,
    _display->clear();
    _display->setTextAlignment(TEXT_ALIGN_CENTER);
    _display->setFont(Roboto_Condensed_16);
    _display->drawString(_display->getWidth() / 2, 0, std::move(strTop));
    _display->drawProgressBar(10, 28, 108, 12, percent);
    _display->drawString(_display->getWidth() / 2, 48, std::move(strBottom));
    _display->display();
  i2cDriver.unlock();
}

void OledDisplayPlugin::addFrame(FrameCallback frame) {
  frames.emplace_back(frame);
  ui->setFrames(frames.data(), frames.size());
}

void OledDisplayPlugin::addOverlay(OverlayCallback overlay) {
  overlays.emplace_back(overlay);
  ui->setOverlays(overlays.data(), overlays.size());
}

bool OledDisplayPlugin::setup() {
  TRY_LOCK(i2cDriver,

    ui->setTargetFPS(CONFIG_OLED_UI_FPS);
    ui->setIndicatorDirection(LEFT_RIGHT);

  //  ui->setIndicatorPosition(RIGHT);
  //  ui->setFrameAnimation(SLIDE_UP);
    ui->setIndicatorPosition(BOTTOM);
    ui->setFrameAnimation(SLIDE_LEFT);

  //  overlays.push_back(timeOverlay);
    overlays.emplace_back(rssiOverlay);
    overlays.emplace_back(deviceIdOverlay);

  //  ui->setFrames(frames.data(), frames.size());
    ui->setOverlays(overlays.data(), overlays.size());

    ui->setActiveSymbol(activeSymbol);
    ui->setInactiveSymbol(inactiveSymbol);

    // Initializing the UI will init the display too
    ui->init();

  //  _display->flipScreenVertically();

    task->configure(1000 / CONFIG_OLED_UI_FPS, _5k, MEDIUM_PRIORITY);
  , return false;);

  return true;
}

bool OledDisplayPlugin::start() {
  return task->start();
}

OledDisplayPlugin::~OledDisplayPlugin() {
  _display->end();
}

void OledDisplayPlugin::execute() {
  if (App.isSetupComplete()) {
    TRY_LOCK(i2cDriver,
      ui->update();
    ,)
  }
}

#endif // CONFIG_ENABLE_I2C_OLED_DISPLAY_PLUGIN
