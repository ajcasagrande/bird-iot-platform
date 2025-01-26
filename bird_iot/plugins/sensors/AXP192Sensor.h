#pragma once
#include "sdkconfig.h"

#if CONFIG_ENABLE_AXP192_SENSOR
#include "common.h"
#include <AXP192.h>

class AXP192SensorClass : public IotPlugin {
public:
  AXP192SensorClass();

  AXP192 axp192;
  bool configured = false;

  bool setup() override;
  bool start() override;

  bool present() {
    return configured;
  }

  double getVcc();

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

extern AXP192SensorClass AXP192Sensor;

#endif // CONFIG_ENABLE_AXP192_SENSOR
