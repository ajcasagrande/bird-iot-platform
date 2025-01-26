#include "SecureWebsocketPlugin.h"
#if CONFIG_ENABLE_SECURE_WEBSOCKET_PLUGIN

#include "esp32-snippets/cpp_utils/SSLUtils.h"
#include "include/certs_private.h"

static const char* TAG = "Secure";

SecureWebsocketPlugin SecureWebsocket;

SecureWebsocketPlugin::SecureWebsocketPlugin() : IotPlugin("Secure Websocket Plugin") { }

bool SecureWebsocketPlugin::setup() {
  SSLUtils::setKey(TLS_KEY);
  SSLUtils::setCertificate(TLS_CERTIFICATE);
  return true;
}
void SecureWebsocketPlugin::onWifiConnected() {
  LOGI(TAG, "starting https server on port 443");
  httpServer.start(443, true);
}
//  void SecureWebsocketPlugin::onWifiDisconnected() { }
//  void SecureWebsocketPlugin::onMqttConnected() { }
//  void SecureWebsocketPlugin::onMqttDisconnected() { }
//  bool SecureWebsocketPlugin::handleMqttMessage(const char *topic, int id, const char *cmd, const JsonDocument& json) {
//   return false; // false means not handled 
// }
//  bool SecureWebsocketPlugin::handleCommand(const std::string& cmd) {
//   return false; // false means not handled 
// }
#if ENABLE_I2C_OLED_DISPLAY_PLUGIN
//  void SecureWebsocketPlugin::addFramesAndOverlays() { }
#endif

#endif // CONFIG_ENABLE_SECURE_WEBSOCKET_PLUGIN
