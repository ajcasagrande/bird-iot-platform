#pragma once
#include "sdkconfig.h"

#if CONFIG_ENABLE_SPI_DISPLAY_PLUGIN

#ifndef CONFIG_ENABLE_SPI_DISPLAY_BUFFER
#define CONFIG_ENABLE_SPI_DISPLAY_BUFFER 0
#endif

#include "common.h"

#include <bb_spi_lcd.h>

struct SPIDisplayUi {
  volatile bool paused = false;
  uint8_t progress = 0;
  int16_t x = 0;
  int16_t y = 0;
  int8_t xVelocity = 1;
  int8_t yVelocity = 1;
  uint8_t font = 2;

  // rotated sizes (width, height) are opposite
  int16_t width = COLOR_HEIGHT;
  int16_t height = COLOR_WIDTH;

  int16_t centerX = width / 2;
  int16_t centerY = height / 2;

//  uint16_t bgColor = color565(43, 43, 43);
  uint16_t bgColor = 0x0000;
  uint16_t fontColor = 0xffff;

  void pause() { paused = true; }
  void resume() { paused = false; }
  bool isPaused() { return paused; }
};

class SPIDisplayPlugin : public IotPlugin {
public:
  SPIDisplayPlugin();
  ~SPIDisplayPlugin();

  Task<SPIDisplayPlugin> *task;
  SPIDisplayUi ui;
  bool setup() override;
  bool start() override;
  void drawScreensaver();
//  void onWifiConnected() override;
//  void onWifiDisconnected() override;
//  void onMqttConnected() override;
//  void onMqttDisconnected() override;
//  bool handleMqttMessage(const char *topic, int id, const char *cmd, const JsonDocument& json) override;
//  bool handleCommand(const std::string& cmd) override;
#if CONFIG_ENABLE_I2C_OLED_DISPLAY_PLUGIN
//  void addFramesAndOverlays() override;
#endif
};

extern SPIDisplayPlugin SPIDisplay;

#endif // CONFIG_ENABLE_SPI_DISPLAY_PLUGIN
