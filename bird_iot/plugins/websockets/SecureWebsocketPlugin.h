#pragma once
#include "sdkconfig.h"

#if CONFIG_ENABLE_SECURE_WEBSOCKET_PLUGIN

#include "common.h"

#include <esp32-snippets/cpp_utils/HttpServer.h>

class SecureWebsocketPlugin : public IotPlugin {
public:
  SecureWebsocketPlugin();

  bool setup() override;
  bool start() override;
  void onWifiConnected() override;
//  void onWifiDisconnected() override;
//  void onMqttConnected() override;
//  void onMqttDisconnected() override;
//  bool handleMqttMessage(const char *topic, int id, const char *cmd, const JsonDocument& json) override;
//  bool handleCommand(const std::string& cmd) override;
#if CONFIG_ENABLE_I2C_OLED_DISPLAY_PLUGIN
//  void addFramesAndOverlays() override;
#endif

private:
  HttpServer httpServer;
};

extern SecureWebsocketPlugin SecureWebsocket;

#endif // CONFIG_ENABLE_SECURE_WEBSOCKET_PLUGIN
