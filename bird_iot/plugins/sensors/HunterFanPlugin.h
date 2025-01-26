#pragma once

#include "sdkconfig.h"

#if CONFIG_ENABLE_HUNTER_FAN_PLUGIN

#include "include/common.h"

class HunterFanPlugin : public IotPlugin {
private:
  int pin;
  int repeats;

  void sendHunterFanCode(uint64_t code, int bits);
public:
  // IotPlugin implementation
  HunterFanPlugin(int, int);
  bool setup() override;
  bool start() override;
  void onMqttConnected() override;
  bool handleMqttMessage(const char *topic, int id, const char *cmd, const JsonDocument& json) override;
};

#endif // CONFIG_ENABLE_HUNTER_FAN_PLUGIN
