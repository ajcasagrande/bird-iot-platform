#pragma once
#include "sdkconfig.h"

#if CONFIG_ENABLE_WEBSOCKET_COMMAND_PLUGIN

#include "common.h"
#include "WebSocketServerPlugin.h"

class WebSocketCommandPlugin : public WebSocketServerPlugin {
public:
  WebSocketCommandPlugin() : WebSocketServerPlugin("WebSocketCommand Plugin", CONFIG_WEBSOCKET_COMMAND_PORT) { }

  void setupWebSocket() override;
  void setupTask() override;
};

extern WebSocketCommandPlugin WebSocketCommand;

#endif // CONFIG_ENABLE_WEBSOCKET_COMMAND_PLUGIN
