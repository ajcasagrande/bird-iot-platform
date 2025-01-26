#pragma once
#include "sdkconfig.h"

#if CONFIG_ENABLE_EXAMPLE_SENSOR_PLUGIN

#include "common.h"

class ExampleSensorPlugin : public BaseSensor {
public:
  ExampleSensorPlugin();

  bool setup() override;
  void poll() override;
  void publishData() override;

//  void onWifiConnected() override;
//  void onWifiDisconnected() override;
//  void onMqttConnected() override;
//  void onMqttDisconnected() override;
//  bool handleMqttMessage(const char *topic, int id, const char *cmd, const JsonDocument& json) override;
//  bool handleCommand(const std::string& cmd) override;
#if ENABLE_I2C_OLED_DISPLAY_PLUGIN
//  void addFramesAndOverlays() override;
#endif

};

#endif // CONFIG_ENABLE_EXAMPLE_SENSOR_PLUGIN
