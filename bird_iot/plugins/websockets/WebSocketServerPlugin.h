#pragma once
#include "sdkconfig.h"
#if CONFIG_ENABLE_WEBSOCKET_SERVER_PLUGIN

#include <WebSocketsServer.h>

#include <vector>
#include "IotPlugin.h"
#include "tasks/TaskClass.h"
#include "Lockable.h"

#define BACKSPACE_KEY 127
#define SPACE_KEY 32
#define COMMAND_BUFFER_SIZE 150

class WebSocketServerPlugin : public IotPlugin, public RecursiveLockable {
public:
  WebSocketsServer ws;
  uint8_t clientStatus = 0;

  WebSocketServerPlugin() : WebSocketServerPlugin("WebSocketServer Plugin", CONFIG_WEBSOCKET_SERVER_PORT) { }
  explicit WebSocketServerPlugin(const char* pluginName, int port);

  bool setup() override;
  bool start() override;
  void onWebSocketEvent(uint8_t clientId, WStype_t type, const uint8_t* payload, size_t length);
  void onWebSocketCommand(uint8_t clientId, char* payload, size_t length);


  virtual void setupTask();
  virtual void startWebSocket();
  virtual void setupWebSocket();

protected:
  VoidTask *task;

  char commandBuffer[COMMAND_BUFFER_SIZE];
  int idx = 0;

};

extern WebSocketServerPlugin WebSocketServer;

#endif
