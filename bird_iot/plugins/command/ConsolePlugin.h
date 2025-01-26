#pragma once
#include "sdkconfig.h"

#if CONFIG_ENABLE_CONSOLE_PLUGIN

#include "common.h"

class ConsolePlugin : public IotPlugin {
public:
  ConsolePlugin();

  bool setup() override;
  bool start() override;
//  void onWifiConnected() override;
//  void onWifiDisconnected() override;
//  void onMqttConnected() override;
//  void onMqttDisconnected() override;
//  bool handleMqttMessage(const char *topic, int id, const char *cmd, const JsonDocument& json) override;
  bool handleCommand(const std::string& cmd) override;
#if CONFIG_ENABLE_I2C_OLED_DISPLAY_PLUGIN
//  void addFramesAndOverlays() override;
#endif

private:
  VoidTask *task;
};

extern ConsolePlugin Console;

#endif // CONFIG_ENABLE_CONSOLE_PLUGIN
