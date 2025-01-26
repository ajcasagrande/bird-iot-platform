#pragma once
#include "sdkconfig.h"

#if CONFIG_ENABLE_CAMERA_SERVER_PLUGIN

#include "include/common.h"

class CameraServerPlugin : public IotPlugin {
public:
  CameraServerPlugin();

  void startCameraServer();

//  bool setup() override;
//  bool start() override;
  void onWifiConnected() override;
//  void onWifiDisconnected() override;
//  void onMqttConnected() override;
//  void onMqttDisconnected() override;
//  bool handleMqttMessage(const char *topic, int id, const char *cmd, const JsonDocument& json) override;
//  bool handleCommand(const std::string& cmd) override;
#if CONFIG_ENABLE_I2C_OLED_DISPLAY_PLUGIN
//  void addFramesAndOverlays() override;
#endif
};

#endif // CONFIG_ENABLE_CAMERA_SERVER_PLUGIN
