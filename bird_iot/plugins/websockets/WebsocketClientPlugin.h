#pragma once
#include "sdkconfig.h"

#if CONFIG_ENABLE_WEBSOCKET_CLIENT_PLUGIN

#include "include/common.h"
#include "Lockable.h"
#include <WebSocketsClient.h>

class ModWebSocketsClient : public WebSocketsClient, public RecursiveLockable {
public:
  WSclient_t getClient() { return _client; }
};

class WebsocketClientPlugin : public IotPlugin {
public:
  WebsocketClientPlugin();

  bool connected() { return client.getClient().status == WSC_CONNECTED; }

//  bool setup() override;
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

  ModWebSocketsClient client;
  Task<WebsocketClientPlugin> *task;
};

extern WebsocketClientPlugin WebsocketClient;

#endif // CONFIG_ENABLE_WEBSOCKET_CLIENT_PLUGIN
