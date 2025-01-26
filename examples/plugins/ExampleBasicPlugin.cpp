#include "ExampleBasicPlugin.h"
#if CONFIG_ENABLE_EXAMPLE_BASIC_PLUGIN

static const char* TAG = "Example";

ExampleBasicPlugin ExampleBasic;

ExampleBasicPlugin::ExampleBasicPlugin() : IotPlugin("Example Basic Plugin") { }

//bool ExampleBasicPlugin::setup() {
//  return true;
//}
//bool ExampleBasicPlugin::start() {
//  return true;
//}
//void ExampleBasicPlugin::onWifiConnected() { }
//void ExampleBasicPlugin::onWifiDisconnected() { }
//void ExampleBasicPlugin::onMqttConnected() { }
//void ExampleBasicPlugin::onMqttDisconnected() { }
//bool ExampleBasicPlugin::handleMqttMessage(const char *topic, int id, const char *cmd, const JsonDocument& json) {
//  return false; // false means not handled
//}
//bool ExampleBasicPlugin::handleCommand(const std::string& cmd) {
//  if (cmd == "Example Basic") {
//    PUTLN("");
//
//  } else {
//    return false; // false means not handled
//  }
//
//  return true;
//}
#if ENABLE_I2C_OLED_DISPLAY_PLUGIN
//void ExampleBasicPlugin::addFramesAndOverlays() { }
#endif

#endif // CONFIG_ENABLE_EXAMPLE_BASIC_PLUGIN
