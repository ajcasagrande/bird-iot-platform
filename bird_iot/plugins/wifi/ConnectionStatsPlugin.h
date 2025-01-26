#pragma once
#include "sdkconfig.h"

#if CONFIG_ENABLE_CONNECTION_STATS_PLUGIN

#include "include/common.h"
#include "ConnectionStats.h"

class ConnectionStatsPlugin : public IotPlugin {
public:
  ConnectionStatsPlugin();

  ConnectionStats wifiStats = ConnectionStats("wifi");
  ConnectionStats mqttStats = ConnectionStats("mqtt");

//  bool setup() override;
//  bool start() override;
  void onWifiConnected() override;
  void onWifiDisconnected() override;
  void onMqttConnected() override;
  void onMqttDisconnected() override;
//  bool handleMqttMessage(const char *topic, int id, const char *cmd, const JsonDocument& json) override;
  bool handleCommand(const std::string& cmd) override;
#if CONFIG_ENABLE_I2C_OLED_DISPLAY_PLUGIN
//  void addFramesAndOverlays() override;
#endif

};

extern ConnectionStatsPlugin ConnectionInfo;

#endif // CONFIG_ENABLE_CONNECTION_STATS_PLUGIN
