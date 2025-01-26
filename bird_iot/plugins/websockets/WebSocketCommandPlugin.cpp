#include "WebSocketCommandPlugin.h"
#if CONFIG_ENABLE_WEBSOCKET_COMMAND_PLUGIN

WebSocketCommandPlugin WebSocketCommand;

static void _execute() {
  WebSocketCommand.ws.loop();
}

static void _onWebSocketCommandEvent(uint8_t clientId, WStype_t type, const uint8_t* payload, size_t length) {
  WebSocketCommand.onWebSocketEvent(clientId, type, payload, length);
}

void WebSocketCommandPlugin::setupTask() {
  task = new VoidTask("WebSocket CMD", _execute);
}

void WebSocketCommandPlugin::setupWebSocket() {
  ws.setAuthorization(CONFIG_WEBSOCKET_SERVER_AUTH);
  ws.onEvent(_onWebSocketCommandEvent);
}

#endif // CONFIG_ENABLE_WEBSOCKET_COMMAND_PLUGIN
