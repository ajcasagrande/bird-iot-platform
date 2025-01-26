#include "HeartbeatTask.h"
#if CONFIG_ENABLE_HEARTBEAT_TASK

#include "ConnectionStatsPlugin.h"

//static const char* TAG = "Heartbeat";

HeartbeatTask Heartbeat;

static void _execute() {
  if (!WifiDriver::connected()) {
#if CONFIG_HEARTBEAT_MONITOR_WIFI
    if (since64(ConnectionInfo.wifiStats.lastDrop) > CONFIG_WIFI_WATCHDOG_TIMEOUT) {
      Device.die("WiFi Watchdog Timeout", RST_WIFI_WATCHDOG, 0, true);
    }
#endif
  } else if (!Mqtt.connected()) {
#if CONFIG_HEARTBEAT_MONITOR_MQTT
    if (since64(ConnectionInfo.mqttStats.lastDrop) > CONFIG_MQTT_WATCHDOG_TIMEOUT) {
      Device.die("MQTT Watchdog Timeout", RST_MQTT_WATCHDOG, 0, true);
    }
#endif
  } else {
#if CONFIG_HEARTBEAT_MONITOR_MQTT_SUBSCRIPTIONS
    // If we still have pending subscriptions and we have been connected to mqtt over the timeout
    if (!Mqtt.subscribeQueue.empty()
        && since64(ConnectionInfo.mqttStats.lastConnection) > CONFIG_MQTT_SUBSCRIPTIONS_WATCHDOG_TIMEOUT) {
      Device.die("MQTT Subscription Watchdog Timeout", RST_MQTT_WATCHDOG, 0, true);
    }
#endif

    // what to do when we are connected
    if (millis() - Heartbeat.lastPublish >= CONFIG_HEARTBEAT_INTERVAL) {
      Heartbeat.lastPublish = millis();
      Device.sendStatus(SafeMode.isActive() ? "safe_mode" : "online");
    }
  }
}

HeartbeatTask::HeartbeatTask() : IotPlugin("Heartbeat") {
  task = new VoidTask("Heartbeat", _execute);
}

bool HeartbeatTask::setup() {
  return task->configure(CONFIG_HEARTBEAT_TASK_CHECK_INTERVAL,
#if CONFIG_ENABLE_AXP192_SENSOR
      _1p75,
#else
      _1p25,
#endif
      MEDIUM_PRIORITY, tskNO_AFFINITY, true, false);
}

bool HeartbeatTask::start() {
  return task->start();
}

//  void HeartbeatTask::onWifiConnected() { }
//  void HeartbeatTask::onWifiDisconnected() { }
//  void HeartbeatTask::onMqttConnected() { }
//  void HeartbeatTask::onMqttDisconnected() { }
//  bool HeartbeatTask::handleMqttMessage(const char *topic, int id, const char *cmd, const JsonDocument& json) {
//   return false; // false means not handled 
// }
//  bool HeartbeatTask::handleCommand(const std::string& cmd) {
//   return false; // false means not handled 
// }
#if ENABLE_I2C_OLED_DISPLAY_PLUGIN
//  void HeartbeatTask::addFramesAndOverlays() { }
#endif

#endif // CONFIG_ENABLE_HEARTBEAT_TASK
