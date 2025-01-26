#pragma once
#include "sdkconfig.h"

#if CONFIG_ENABLE_QMC5883L_COMPASS_SENSOR

#include "common.h"
#include <QMC5883L.h>

class QMC5883LCompass;

#if CONFIG_ENABLE_TFT_DISPLAY
#include "tft_includes.h"
#include <dejavu_sans.h>

class CompassOverlay : public StringDrawable<QMC5883LCompass> {
public:
  explicit CompassOverlay(QMC5883LCompass *plugin);
  void updateCurrent() override { }
  StringRenderInfo getRenderInfo(TFT_eSPI *img, DisplayUI& ui, int16_t textWidth) override;
};

#endif

class QMC5883LCompass : public BaseSensor {
public:
  QMC5883LCompass();

  QMC5883L compass;

  bool setup() override;
  void poll() override;
  void publishData() override;
#if CONFIG_ENABLE_TFT_DISPLAY
  CompassOverlay compassOverlay;
#endif

//  void onWifiConnected() override;
//  void onWifiDisconnected() override;
//  void onMqttConnected() override;
//  void onMqttDisconnected() override;
//  bool handleMqttMessage(const char *topic, int id, const char *cmd, const JsonDocument& json) override;
//  bool handleCommand(const std::string& cmd) override;
#if ENABLE_I2C_OLED_DISPLAY_PLUGIN
//  void addFramesAndOverlays() override;
#endif
#if CONFIG_ENABLE_TFT_DISPLAY
  void displayDirection(const char *dir);
#endif
};

#endif // CONFIG_ENABLE_QMC5883L_COMPASS_SENSOR
