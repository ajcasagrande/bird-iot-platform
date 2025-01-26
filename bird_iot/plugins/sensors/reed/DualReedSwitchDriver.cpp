#include "DualReedSwitchDriver.h"

#if CONFIG_ENABLE_REED_SWITCH_DRIVER

void _poll(DualReedSwitchDriver *driver) {
  driver->poll();
}

DualReedSwitchDriver::DualReedSwitchDriver(const char* subTopic, const char* pubTopic) : 
    IotPlugin("Dual Reed Switch Driver"), _subTopic(subTopic), _pubTopic(pubTopic) { 
  
  pollTask = new Task<DualReedSwitchDriver>("Dual Reed Poll", this, _poll); 
}

bool DualReedSwitchDriver::setup() {
  openSwitch = App.profile.openReedSwitch;
  closedSwitch = App.profile.closedReedSwitch;

  if (openSwitch == nullptr && closedSwitch == nullptr) {
    return false;
  }

  if (openSwitch != nullptr) {
    openSwitch->setup();
  }
  if (closedSwitch != nullptr) {
    closedSwitch->setup();
  }

  return pollTask->configure(50, _2k, LOW_PRIORITY);
}

bool DualReedSwitchDriver::start() {
  return pollTask->start();
}

void DualReedSwitchDriver::poll() {
  int state = pollInternal();

  if (currentState != state) {
    alertState(state);
  }
  currentState = state;
}

int DualReedSwitchDriver::pollInternal() {
  if (openSwitch != nullptr && closedSwitch != nullptr) {
    uint8_t o = openSwitch->read();
    uint8_t c = openSwitch->read();
    if (o == REED_SWITCH_DISCONNECTED && c == REED_SWITCH_DISCONNECTED) {
      // if they are both OPEN/disconnected that means the door is not fully open or fully closed so partially open/closed
      return PARTIALLY_OPEN;
    } else if (o == REED_SWITCH_CONNECTED) {
      // note that if the "open switch" is closed/connected that means the door is OPEN
      return OPEN;
    } else if (c == REED_SWITCH_CONNECTED) {
      return CLOSED;
    }
    // if for whatever reason they are both CLOSED this state is undefined because
    // the door cannot be both fully open AND fully closed simultaneously
    // most likely the result of testing or install error
    return UNKNOWN_STATE;

  } else if (openSwitch != nullptr) {
    // note that if the "open switch" is closed/connected that means the door is OPEN
    return openSwitch->read() == REED_SWITCH_CONNECTED ? OPEN : CLOSED;

  } else if (closedSwitch != nullptr) {
    return closedSwitch->read() == REED_SWITCH_CONNECTED ? CLOSED : OPEN;
  }

  return UNKNOWN_STATE;
}

void DualReedSwitchDriver::alertState(int state) {
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

  Mqtt.publish(_pubTopic, doc);
}

bool DualReedSwitchDriver::handleMqttMessage(const char *topic, const int id, const char *cmd, const JsonDocument& json) {
  if (strcmp(topic, _subTopic) == 0
      && strcmp(cmd, "status") == 0) {
    alertState(currentState);
    Mqtt.respondTrue(id);
    return true;
  }
  return false;
}

void DualReedSwitchDriver::onMqttConnected() {
  Mqtt.subscribe(_subTopic);
}

#endif // CONFIG_ENABLE_REED_SWITCH_DRIVER
