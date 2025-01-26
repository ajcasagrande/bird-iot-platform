#include "WebSocketServerPlugin.h"

#if CONFIG_ENABLE_WEBSOCKET_SERVER_PLUGIN

#include <Streaming.h>
#include <common.h>
#include "include/logging.h"
#include "WebsocketWrapper.h"
#include "IotApp.h"

WebSocketServerPlugin WebSocketServer;

static const char* TAG = "WebSocket";

static void _execute() {
  WebSocketServer.ws.loop();
}

WebSocketServerPlugin::WebSocketServerPlugin(const char* pluginName, int port) : IotPlugin(pluginName), ws(port) {
}

void WebSocketServerPlugin::onWebSocketCommand(uint8_t clientId, char* payload, size_t length) {
  idx = 0;

  if (length == 0) {
    putErr("empty command specified");
    return;
  } else if (length >= COMMAND_BUFFER_SIZE) {
    putErr("command too long!");
    return;
  }

  payload[length] = '\0';
//  put("websocket command: '" << payload << "'");

  if (strcmp(payload, "quit") == 0
   || strcmp(payload, "exit") == 0
   || strcmp(payload, "disconnect") == 0) {

    putWarn("client " BOLD_STYLE << clientId << NORMAL_STYLE << " has requested to be disconnected.");
    ws.disconnect(clientId);
    return;
  }

  for (auto & plugin : App.getPlugins()) {
    if (plugin->handleCommand(payload)) {
//      put("command was handled by " << plugin->name);
      return;
    }
  }

  putWarn("unknown command: " BOLD_STYLE << payload);
}

void WebSocketServerPlugin::onWebSocketEvent(uint8_t clientId, WStype_t type, const uint8_t* payload, size_t length) {
  bool controlCode = false;
  switch(type) {
    case WStype_CONNECTED:
      this->clientStatus |= (0x1 << clientId);
//      putWarn(BOLD_STYLE "web socket connected for client " << clientId);
      char str[60];
      xsnprintf(str, 60, LOG_COLOR_W BOLD_STYLE "web socket connected for client %d" LOG_RESET_COLOR " \r\n", clientId);
      WebsocketWrapper::sendTXT(this, (uint8_t *) str, strlen(str), false);
      break;

    case WStype_DISCONNECTED:
      this->clientStatus &= ~(0x1 << clientId);
      LOGW(TAG, "web socket disconnected for client " << clientId);
      break;

    case WStype_TEXT:
      char c;
      for (size_t i = 0; i < length; i++) {
        c = (char)payload[i];
        if (c == '\r' || c == '\n') {
          if (length == 1) {
            WebsocketWrapper::sendTXT(this, (uint8_t *) "\r\n", 2, false);
          }

          if (idx <= 0) {
            idx = 0;
            length = 0;
            continue;
          }
          this->onWebSocketCommand(clientId, (char*)commandBuffer, idx);
          idx = 0;
          length = 0;
        } else if (c == BACKSPACE_KEY) {
          if (length == 1) {
            WebsocketWrapper::sendTXT(this, (uint8_t *) "\b \b", 3, false);
          }
          length = 0;
          if (--idx < 0) {
            idx = 0;
          }
        } else if (c == '[' || c == '^') {
          controlCode = true;
        } else {
          if ((c >= 'A' && c <= 'Z') ||
              (c >= 'a' && c <= 'z') ||
              (c >= '0' && c <= '9') ||
              c == SPACE_KEY ||
              c == '-'
            ) {
            if (controlCode) {
              // control codes skip the next valid char
              controlCode = false;
              continue;
            } else if (idx < (COMMAND_BUFFER_SIZE - 2)) {
              commandBuffer[idx++] = c;
              // only echo if length is 1 char (direct echo ala tty)
              if (length == 1) {
                WebsocketWrapper::sendTXT(this, (uint8_t *)&c, 1, false);
              }
            } else {
              length = 0;
              putErr("buffer full");
            }
          }
        }
      }
      break;

    default:
      // do nothing
      break;
  }
}

static void _onWebSocketEvent(uint8_t clientId, WStype_t type, const uint8_t* payload, size_t length) {
  WebSocketServer.onWebSocketEvent(clientId, type, payload, length);
}

bool WebSocketServerPlugin::setup() {
  setupTask();
  setupWebSocket();
  // Use Core 0 for better performance
  // allocate extra for using sprintf
  return task->configure(50, _3p5, MEDIUM_HIGH_PRIORITY, CORE_0, false, true);
}

void WebSocketServerPlugin::setupTask() {
  task = new VoidTask("WebSocket", _execute);
}

void WebSocketServerPlugin::setupWebSocket() {
  ws.setAuthorization(CONFIG_WEBSOCKET_SERVER_AUTH);
  ws.onEvent(_onWebSocketEvent);
}

bool WebSocketServerPlugin::start() {
  startWebSocket();
  return task->start();
}

void WebSocketServerPlugin::startWebSocket() {
  ws.begin();
}

#endif // CONFIG_ENABLE_WEBSOCKET_SERVER_PLUGIN
