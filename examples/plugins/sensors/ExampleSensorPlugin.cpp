#include "ExampleSensorPlugin.h"

#if CONFIG_ENABLE_EXAMPLE_SENSOR_PLUGIN

static const char* TAG = "Example Sensor";

ExampleSensorPlugin::ExampleSensorPlugin() : BaseSensor("Example Sensor Plugin", "Example Sensor") {

}

bool ExampleSensorPlugin::setup() {
  // todo
  return pollTask->configure(CONFIG_EXAMPLE_SENSOR_PLUGIN_POLL_INTERVAL, _1p75, MEDIUM_PRIORITY)
          && publishTask->configure(CONFIG_EXAMPLE_SENSOR_PLUGIN_PUBLISH_INTERVAL, _1p75, MEDIUM_PRIORITY);
}

void ExampleSensorPlugin::poll() {
  // todo
}

void ExampleSensorPlugin::publishData() {
  // todo
}

//  void ExampleSensorPlugin::onWifiConnected() { }
//  void ExampleSensorPlugin::onWifiDisconnected() { }
//  void ExampleSensorPlugin::onMqttConnected() { }
//  void ExampleSensorPlugin::onMqttDisconnected() { }
//  bool ExampleSensorPlugin::handleMqttMessage(const char *topic, int id, const char *cmd, const JsonDocument& json) { 
//    return false; // false means not handled
//  }
//bool ExampleSensorPlugin::handleCommand(const std::string& cmd) {
//  if (cmd == "Example Sensor") {
//    PUTLN("");
//
//  } else {
//    return false; // false means not handled
//  }
//
//  return true;
//}
#if ENABLE_I2C_OLED_DISPLAY_PLUGIN
//  void ExampleSensorPlugin::addFramesAndOverlays() { }
#endif

#endif // CONFIG_ENABLE_EXAMPLE_SENSOR_PLUGIN
