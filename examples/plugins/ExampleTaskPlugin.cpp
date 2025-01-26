#include "ExampleTaskPlugin.h"
#if CONFIG_ENABLE_EXAMPLE_TASK_PLUGIN

static const char* TAG = "Example Task";

ExampleTaskPlugin ExampleTask;

static void _execute(ExampleTaskPlugin *plugin) {
  plugin->execute();
}

ExampleTaskPlugin::ExampleTaskPlugin() : IotPlugin("Example Task Plugin") {
  task = new Task<ExampleTaskPlugin>("Example Task Plugin", this, _execute);
}

bool ExampleTaskPlugin::setup() {
  // todo
  return task->configure(100, _2p5, MEDIUM_PRIORITY);
}
bool ExampleTaskPlugin::start() {
  // todo
  return task->start();
}

void ExampleTaskPlugin::execute() {
  // todo
}

//  void ExampleTaskPlugin::onWifiConnected() { }
//  void ExampleTaskPlugin::onWifiDisconnected() { }
//  void ExampleTaskPlugin::onMqttConnected() { }
//  void ExampleTaskPlugin::onMqttDisconnected() { }
//  bool ExampleTaskPlugin::handleMqttMessage(const char *topic, int id, const char *cmd, const JsonDocument& json) {
//    return false; // false means not handled
//  }
//bool ExampleTaskPlugin::handleCommand(const std::string& cmd) {
//  if (cmd == "Example Task") {
//    PUTLN("");
//
//  } else {
//    return false; // false means not handled
//  }
//
//  return true;
//}
#if ENABLE_I2C_OLED_DISPLAY_PLUGIN
//  void ExampleTaskPlugin::addFramesAndOverlays() { }
#endif

#endif // CONFIG_ENABLE_EXAMPLE_TASK_PLUGIN
