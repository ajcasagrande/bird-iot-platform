#pragma once
#include "sdkconfig.h"

#if CONFIG_ENABLE_RC_LIGHTS_PLUGIN

#include "common.h"

class RcLightsPlugin : public IotPlugin {
private:
  NeoPixelDriver* driver;

public:
  explicit RcLightsPlugin(NeoPixelDriver* neoPixelDriver);

  bool setup() override;
  bool start() override;
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

#endif // CONFIG_ENABLE_RC_LIGHTS_PLUGIN
