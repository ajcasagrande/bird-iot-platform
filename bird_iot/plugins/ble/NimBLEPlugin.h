#pragma once
#include "sdkconfig.h"

#if CONFIG_ENABLE_NIMBLE_PLUGIN

#include "include/common.h"

class NimBLEPlugin : public IotPlugin {
public:
  NimBLEPlugin();

  Task<NimBLEPlugin> *task;
  bool setup() override;
  bool start() override;
  void destroy();
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

extern NimBLEPlugin NimBLE;

#endif // CONFIG_ENABLE_NIMBLE_PLUGIN
