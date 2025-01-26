#include "ConnectionStatsPlugin.h"
#if CONFIG_ENABLE_CONNECTION_STATS_PLUGIN

ConnectionStatsPlugin ConnectionInfo;

ConnectionStatsPlugin::ConnectionStatsPlugin() : IotPlugin("Connection Stats Plugin") { }

//  bool ConnectionStatsPlugin::setup() {
//   return true;
// }

void ConnectionStatsPlugin::onWifiConnected() {
  wifiStats.onConnect();
}

void ConnectionStatsPlugin::onWifiDisconnected() {
  wifiStats.onDisconnect();
}

void ConnectionStatsPlugin::onMqttConnected() {
  mqttStats.onConnect();

  Device.sendAlert(ALERT_MQTT_CONNECTED, json_lambda(1,, js["drops"] = ConnectionInfo.mqttStats.drops));
}

void ConnectionStatsPlugin::onMqttDisconnected() {
  mqttStats.onDisconnect();
}

//  bool ConnectionStatsPlugin::handleMqttMessage(const char *topic, int id, const char *cmd, const JsonDocument& json) {
//   return false; // false means not handled 
// }

bool ConnectionStatsPlugin::handleCommand(const std::string& cmd) {
  if (cmd == "conn") {
    mqttStats.printStats();
    wifiStats.printStats();
  } else {
    return false; // false means not handled
  }
  return true;
}

#if CONFIG_ENABLE_I2C_OLED_DISPLAY_PLUGIN
//  void ConnectionStatsPlugin::addFramesAndOverlays() { }
#endif

#endif // CONFIG_ENABLE_CONNECTION_STATS_PLUGIN
