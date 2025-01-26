#pragma once

#include "sdkconfig.h"
#include <sys/cdefs.h>

#include "WebSocketServerPlugin.h"
#include "WebsocketClientPlugin.h"
#include "streams/BufferedStreamJoiner.h"
#include "streams/DirectStreamJoiner.h"
#include "streams/StringBufferedStream.h"
#include "logging.h"

#define put(stream) BufferedStreamJoiner << LOG_COLOR(LOG_COLOR_WHITE) << stream << LOG_RESET_COLOR << endl
#define putWarn(stream) BufferedStreamJoiner << LOG_COLOR_W << stream << LOG_RESET_COLOR << endl
#define putErr(stream) BufferedStreamJoiner << LOG_COLOR_E << stream << LOG_RESET_COLOR << endl
#define putf(format, ...) BufferedStreamJoiner.printf(LOG_COLOR(LOG_COLOR_WHITE) format LOG_RESET_COLOR "\r\n", ##__VA_ARGS__)
#define putValf(prefixLength, prefix, format, ...) putf(BOLD("%" #prefixLength "s") " | " format, prefix, ##__VA_ARGS__)
#define putStringVal(prefixLength, prefix, ...) putf(BOLD("%" #prefixLength "s") " | %s", prefix, ##__VA_ARGS__)
#define putHelp(prefix, ...) putValf(15, prefix, "%s", ##__VA_ARGS__)
#define putln() BufferedStreamJoiner << endl

class WebsocketWrapper {
public:
  static bool isActive() {
    return false
  #if CONFIG_ENABLE_WEBSOCKET_SERVER_PLUGIN
    || WebSocketServer.clientStatus > 0
  #endif
  #if CONFIG_ENABLE_WEBSOCKET_CLIENT_PLUGIN
    || WebsocketClient.connected()
  #endif
    ;
  }

#if CONFIG_ENABLE_WEBSOCKET_SERVER_PLUGIN
  static void sendTXT(WebSocketServerPlugin* websocket, uint8_t * payload, size_t length, bool headerToPayload) {
    TRY_LOCK(*websocket,
      if (websocket->clientStatus > 0) {
        websocket->ws.broadcastTXT(payload, length, headerToPayload);
      }
    ,);
  }
#endif

  static void sendTXT(uint8_t * payload, size_t length, bool headerToPayload) {
#if CONFIG_ENABLE_WEBSOCKET_SERVER_PLUGIN
    TRY_LOCK(WebSocketServer,
      if (WebSocketServer.clientStatus > 0) {
        WebSocketServer.ws.broadcastTXT(payload, length, headerToPayload);
      }
    ,);
#endif
#if CONFIG_ENABLE_WEBSOCKET_CLIENT_PLUGIN
    TRY_LOCK(WebSocketServer,
      if (WebsocketClient.connected()) {
        WebsocketClient.client.sendTXT(payload, length, headerToPayload);
      }
    ,);
#endif
  }

  static void disconnectAll() {
#if CONFIG_ENABLE_WEBSOCKET_SERVER_PLUGIN
    static const char* TAG = "WebsocketWrapper";
    LOGD(TAG, "Disconnecting all clients");
    BufferedStreamJoiner.bufferedStream.flush();
    WebSocketServer.ws.disconnect();
#endif
#if CONFIG_ENABLE_WEBSOCKET_CLIENT_PLUGIN
    // todo
    //    WebsocketClient.client.disconnect();
#endif
  }

};

