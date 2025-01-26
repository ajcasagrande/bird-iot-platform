#include "WebsocketClientPlugin.h"
#if CONFIG_ENABLE_WEBSOCKET_CLIENT_PLUGIN

#include "include/certs.h"

const static char* TAG = "WSS Client";

WebsocketClientPlugin WebsocketClient;

WebsocketClientPlugin::WebsocketClientPlugin() : IotPlugin("Websocket Client Plugin") { }

static void _execute(WebsocketClientPlugin *plugin) {
  plugin->client.loop();
}

//  bool WebsocketClientPlugin::setup() {
//   return true;
// }
void WebsocketClientPlugin::onWifiConnected() {
  if (task == nullptr) {
    task = new Task<WebsocketClientPlugin>("WSS Client", this, _execute);
    task->configure(250, _5k, MEDIUM_LOW_PRIORITY, tskNO_AFFINITY, false, true);
    LOGI(TAG, "connecting websocket client to server...");
    auto url = std::string("/") + deviceId();
    client.beginSslWithCA("bird-iot", 8765, url.c_str(), OTA_CA_CERTIFICATE, "wss");
    client.enableHeartbeat((uint32_t)(WEBSOCKETS_TCP_TIMEOUT * 0.8), 250, 0);
  }
}

bool WebsocketClientPlugin::start() {
  return task->start();
}

//  void WebsocketClientPlugin::onWifiDisconnected() { }
//  void WebsocketClientPlugin::onMqttConnected() { }
//  void WebsocketClientPlugin::onMqttDisconnected() { }
//  bool WebsocketClientPlugin::handleMqttMessage(const char *topic, int id, const char *cmd, const JsonDocument& json) {
//   return false; // false means not handled 
// }
//  bool WebsocketClientPlugin::handleCommand(const std::string& cmd) {
//   return false; // false means not handled 
// }
#if CONFIG_ENABLE_I2C_OLED_DISPLAY_PLUGIN
//  void WebsocketClientPlugin::addFramesAndOverlays() { }
#endif

#endif // CONFIG_ENABLE_WEBSOCKET_CLIENT_PLUGIN
