#include "SPIDisplayPlugin.h"
#if CONFIG_ENABLE_SPI_DISPLAY_PLUGIN

static const char* TAG = "SPI Display";

SPIDisplayPlugin SPIDisplay;

static const uint16_t usPal[] = {0xf800, 0x07e0, 0x001f, 0x7ff, 0xf81f, 0xffe0, 0xffff, 0x0000};
int i, iFG, x, y, r1, r2;

SPIDisplayPlugin::SPIDisplayPlugin() : IotPlugin("SPI Display Plugin") { }

SPIDisplayPlugin::~SPIDisplayPlugin() {
#if CONFIG_ENABLE_SPI_DISPLAY_BUFFER
  spilcdFreeBackbuffer();
#endif
}

void _render(SPIDisplayPlugin *plugin) {
  plugin->drawScreensaver();
}

bool SPIDisplayPlugin::setup() {
  spilcdInit(LCD_ST7789_135, 0, 0, 0, 32000000, 5, 16, -1, 4, -1, 19, 18); // TTGO T-Display pin numbering, 40Mhz
  spilcdSetOrientation(LCD_ORIENTATION_ROTATED);
#if CONFIG_ENABLE_SPI_DISPLAY_BUFFER
  spilcdAllocBackbuffer();
#endif
  task = new Task<SPIDisplayPlugin>("SPI Display", this, _render);
  return task->configure(33, _4k, 12, CORE_0, true, false);
}

bool SPIDisplayPlugin::start() {
  return task->start();
}

void SPIDisplayPlugin::drawScreensaver() {
  if (!ui.isPaused()) {
#if CONFIG_ENABLE_SPI_DISPLAY_BUFFER
    spilcdShowBuffer(0,0,ui.width, ui.height);
#endif
    // clear out the old one
    spilcdWriteString(ui.x, ui.y, (char*)deviceId(), ui.bgColor, ui.bgColor, FONT_NORMAL, !CONFIG_ENABLE_SPI_DISPLAY_BUFFER);

    ui.x += ui.xVelocity;
    ui.y += ui.yVelocity;
    if (ui.x >= ui.width - (8 * strlen(deviceId())) || ui.x <= 0) {
      ui.xVelocity *= -1;
      ui.fontColor = randomColor();
    }
    if (ui.y >= ui.height - 8 || ui.y <= 0) {
      ui.yVelocity *= -1;
      ui.fontColor = randomColor();
    }

    spilcdWriteString(ui.x, ui.y, (char*)deviceId(), ui.fontColor, ui.bgColor, FONT_NORMAL, !CONFIG_ENABLE_SPI_DISPLAY_BUFFER);
  }
}

//  void SPIDisplayPlugin::onWifiConnected() { }
//  void SPIDisplayPlugin::onWifiDisconnected() { }
//  void SPIDisplayPlugin::onMqttConnected() { }
//  void SPIDisplayPlugin::onMqttDisconnected() { }
//  bool SPIDisplayPlugin::handleMqttMessage(const char *topic, int id, const char *cmd, const JsonDocument& json) {
//   return false; // false means not handled 
// }
//  bool SPIDisplayPlugin::handleCommand(const std::string& cmd) {
//   return false; // false means not handled 
// }
#if ENABLE_I2C_OLED_DISPLAY_PLUGIN
//  void SPIDisplayPlugin::addFramesAndOverlays() { }
#endif

#endif // CONFIG_ENABLE_SPI_DISPLAY_PLUGIN
