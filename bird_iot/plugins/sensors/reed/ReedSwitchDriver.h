#pragma once

#include "sdkconfig.h"

#if CONFIG_ENABLE_REED_SWITCH_DRIVER

#include "include/common.h"
#include "ReedSwitch.h"

#define UNKNOWN_STATE -1
#define CLOSED 0
#define OPEN 1
#define PARTIALLY_OPEN 2

class ReedSwitchDriver : public IotPlugin {
private:
  int currentState = UNKNOWN_STATE;
  std::vector<ReedSwitch> switches;
  int pollInternal();
  Task<ReedSwitchDriver> *pollTask;

public:
  void poll();
  void alertState(int state);

  ReedSwitchDriver();
  bool setup() override;
  bool start() override;
  bool handleMqttMessage(const char *topic, int id, const char *cmd, const JsonDocument& json) override;
};

#endif
