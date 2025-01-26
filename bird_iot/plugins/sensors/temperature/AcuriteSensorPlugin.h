#pragma once
#include "sdkconfig.h"

#if CONFIG_ENABLE_ACURITE_SENSOR_PLUGIN

#include "common.h"

class AcuriteSensorPlugin : public IotPlugin {
public:
  AcuriteSensorPlugin();

  bool setup() override;
  bool start() override;
  void execute();

//  void onWifiConnected() override;
//  void onWifiDisconnected() override;
//  void onMqttConnected() override;
//  void onMqttDisconnected() override;
//  bool handleMqttMessage(const char *topic, int id, const char *cmd, const JsonDocument& json) override;
//  bool handleCommand(const std::string& cmd) override;
#if ENABLE_I2C_OLED_DISPLAY_PLUGIN
//  void addFramesAndOverlays() override;
#endif

private:
  Task<AcuriteSensorPlugin> *task;

};

extern AcuriteSensorPlugin AcuriteSensor;

#endif // CONFIG_ENABLE_ACURITE_SENSOR_PLUGIN
