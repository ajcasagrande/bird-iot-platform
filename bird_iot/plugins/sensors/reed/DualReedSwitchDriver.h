#pragma once

#include "sdkconfig.h"

#if CONFIG_ENABLE_REED_SWITCH_DRIVER

#include "include/common.h"
#include "ReedSwitch.h"

#define UNKNOWN_STATE -1
#define CLOSED 0
#define OPEN 1
#define PARTIALLY_OPEN 2
#define REED_SWITCH_CONNECTED 0
#define REED_SWITCH_DISCONNECTED 1

class DualReedSwitchDriver : public IotPlugin {
private:
  int currentState = UNKNOWN_STATE;
  ReedSwitch *openSwitch;
  ReedSwitch *closedSwitch;
  int pollInternal();
  const char* _subTopic;
  const char* _pubTopic;
  Task<DualReedSwitchDriver> *pollTask;

public:
  DualReedSwitchDriver(const char* subTopic, const char* pubTopic);

  void poll();
  void alertState(int state);
  bool setup() override;
  bool start() override;
  void onMqttConnected() override;
  bool handleMqttMessage(const char *topic, int id, const char *cmd, const JsonDocument& json) override;
};

#endif // CONFIG_ENABLE_REED_SWITCH_DRIVER
