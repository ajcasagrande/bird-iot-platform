#pragma once
#include "sdkconfig.h"

#if CONFIG_ENABLE_RSSI_STATS_PLUGIN
#include <Ticker.h>
#include <esp_wifi_types.h>
#include "util/FloatStats.h"
#include "IotPlugin.h"
#include "tasks/TaskClass.h"
#include <string>

class RssiPlugin : public IotPlugin {
private:
  FloatStats stats = FloatStats("Rssi");
  wifi_ap_record_t info;
  Task<RssiPlugin> *pollTask;
  Task<RssiPlugin> *publishTask;

public:
  void poll();
  void publishData();

  // IotPlugin implementation
  RssiPlugin();
  bool setup() override;
  bool start() override;
  void onMqttConnected() override;
  bool handleMqttMessage(const char *topic, int id, const char *cmd, const JsonDocument& json) override;
  bool handleCommand(const std::string& cmd) override;
};

extern RssiPlugin RssiStats;

#endif // CONFIG_ENABLE_RSSI_STATS_PLUGIN
