#pragma once
#include "sdkconfig.h"

#if CONFIG_ENABLE_HEARTBEAT_TASK

#include "common.h"

class HeartbeatTask : public IotPlugin {
public:
  HeartbeatTask();

  uint32_t lastPublish;

  bool setup() override;
  bool start() override;
//  void onWifiConnected() override;
//  void onWifiDisconnected() override;
//  void onMqttConnected() override;
//  void onMqttDisconnected() override;
//  bool handleMqttMessage(const char *topic, int id, const char *cmd, const JsonDocument& json) override;
//  bool handleCommand(const std::string& cmd) override;
#if ENABLE_I2C_OLED_DISPLAY_PLUGIN
//  void addFramesAndOverlays() override;
#endif

private:
  VoidTask *task;
};

extern HeartbeatTask Heartbeat;

#endif // CONFIG_ENABLE_HEARTBEAT_TASK
