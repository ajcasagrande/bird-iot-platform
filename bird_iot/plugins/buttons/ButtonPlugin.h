#pragma once
#include "sdkconfig.h"

#if CONFIG_ENABLE_BUTTON_PLUGIN

#include "common.h"
#include "IotButton.h"
#include <EasyButton.h>

class ButtonPluginClass : public IotPlugin {
public:
  ButtonPluginClass();

  std::vector<IotButton*> buttons;

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

  VoidTask *task;
};

extern ButtonPluginClass ButtonPlugin;

#endif // CONFIG_ENABLE_BUTTON_PLUGIN
