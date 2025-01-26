#include "CameraServerPlugin.h"
#if CONFIG_ENABLE_CAMERA_SERVER_PLUGIN

#include "esp_http_server.h"

static const char* TAG = "Camera Server";

CameraServerPlugin::CameraServerPlugin() : IotPlugin("Camera Server Plugin") { }

httpd_handle_t stream_httpd = nullptr;

static esp_err_t stream_handler(httpd_req_t *req) {
  esp_err_t res;

  res = httpd_resp_set_type(req, "text/plain");
  if (res != ESP_OK) {
    return res;
  }

  res = httpd_resp_sendstr(req, "It Works!");
  return res;
}

void CameraServerPlugin::startCameraServer() {
  httpd_config_t config = HTTPD_DEFAULT_CONFIG();
  config.server_port = 80;

  httpd_uri_t index_uri = {
      .uri       = "/",
      .method    = HTTP_GET,
      .handler   = stream_handler,
      .user_ctx  = nullptr
  };

  LOGD(TAG, "Starting web server on port: " << config.server_port);
  if (httpd_start(&stream_httpd, &config) == ESP_OK) {
    httpd_register_uri_handler(stream_httpd, &index_uri);
  }
}

//  bool CameraServerPlugin::setup() {
//   return true;
// }
void CameraServerPlugin::onWifiConnected() {
  if (stream_httpd == nullptr) {
    startCameraServer();
  }
}
//  void CameraServerPlugin::onWifiDisconnected() { }
//  void CameraServerPlugin::onMqttConnected() { }
//  void CameraServerPlugin::onMqttDisconnected() { }
//  bool CameraServerPlugin::handleMqttMessage(const char *topic, int id, const char *cmd, const JsonDocument& json) {
//   return false; // false means not handled 
// }
//  bool CameraServerPlugin::handleCommand(const std::string& cmd) {
//   return false; // false means not handled 
// }
#if CONFIG_ENABLE_I2C_OLED_DISPLAY_PLUGIN
//  void CameraServerPlugin::addFramesAndOverlays() { }
#endif

#endif // CONFIG_ENABLE_CAMERA_SERVER_PLUGIN
