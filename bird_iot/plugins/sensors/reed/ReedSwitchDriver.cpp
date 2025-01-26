#include "ReedSwitchDriver.h"

#if CONFIG_ENABLE_REED_SWITCH_DRIVER

#include "include/topics.h"

void _poll(ReedSwitchDriver* plugin) {
  plugin->poll();
}

ReedSwitchDriver::ReedSwitchDriver() : IotPlugin("Reed Switch Driver") { 
  pollTask = new Task<ReedSwitchDriver>("Reed Poll", this, _poll);
}

bool ReedSwitchDriver::setup() {
  switches = App.profile.reedSwitches;
  for (auto &sw : switches) {
    sw.setup();
  }

  return pollTask->configure(100, _4k, MEDIUM_HIGH_PRIORITY);
}

bool ReedSwitchDriver::start() {
  return pollTask->start();
}

void ReedSwitchDriver::poll() {
  int state = pollInternal();

  if (currentState != state) {
    alertState(state);
  }
  currentState = state;
}

int ReedSwitchDriver::pollInternal() {
  uint8_t openCount = 0;
  uint8_t closedCount = 0;

  for (auto & sw : switches) {
    if (sw.read() == OPEN) {
      openCount++;
    } else {
      closedCount++;
    }
  }

  if (openCount == switches.size()) {
    return OPEN;
  } else if (closedCount == switches.size()) {
    return CLOSED;
  } else {
    return PARTIALLY_OPEN;
  }
}

void ReedSwitchDriver::alertState(int state) {
  const char* status;
  if (state == OPEN) {
    status = "open";
  } else if (state == CLOSED) {
    status = "closed";
  } else if (state == PARTIALLY_OPEN) {
    status = "partially_open";
  } else {
    status = "unknown";
  }

  const size_t capacity = JSON_OBJECT_SIZE(2);
  DynamicJsonDocument doc(capacity);
  doc["sensor"] = "reed_switch";
  doc["status"] = status;

  // todo: change topic?
  Mqtt.publish(Mqtt.topics.garage, doc);
}

bool ReedSwitchDriver::handleMqttMessage(const char *topic, const int id, const char *cmd, const JsonDocument& json) {
  if (strcmp(topic, GARAGE_MQTT_TOPIC) == 0
      && strcmp(cmd, "status") == 0) {
    alertState(currentState);
    Mqtt.respondTrue(id);
    return true;
  }
  return false;
}

#endif // CONFIG_ENABLE_REED_SWITCH_DRIVER
