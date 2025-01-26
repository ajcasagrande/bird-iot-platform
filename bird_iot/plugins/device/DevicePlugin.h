#pragma once

#include "include/common.h"


typedef enum {
  RST_UNKNOWN = 0,
  RST_OTA_COMPLETE = 30,
  RST_OTA_FAILURE = 31,
  RST_RESET_BY_COMMAND = 32,
  RST_OTA_DEADMANS_SWITCH = 33,
  RST_OTA_RTOS_TASK = 34,
  RST_WIFI_WATCHDOG = 35,
  RST_MQTT_WATCHDOG = 36,
  RST_MQTT_SUB_WATCHDOG = 37,
} birdiot_reset_reason_t;


class DevicePlugin : public IotPlugin {
private:
  const char* currentStatus = "initializing";
  bool sentBootInfo = false;
  bool sentCpuInfo = false;

public:
  DevicePlugin() : IotPlugin("Device Plugin") { }

//  void onWifiDisconnected() override;
//  void onMqttDisconnected() override;
  void onMqttConnected() override;
//  void onWifiConnected() override;
  bool handleMqttMessage(const char *topic, int id, const char *cmd, const JsonDocument& json) override;

  void die(const char* reason, birdiot_reset_reason_t hint, uint32_t wait = 0, bool error = true) __attribute__ ((noreturn));
  static void hard_reset(birdiot_reset_reason_t hint) __attribute__ ((noreturn));
  bool sendStatus(const char* status);
  bool sendAlert(AlertCode code, const char* severity, const char* message, size_t extraCapacity=0, const std::function<void(JsonObject)>& optionalLambda=nullptr);
  static bool sendBootInfo();
  static bool sendCpuInfo();
  static const char* getStatusByAlert(AlertCode code);

  bool sendAlertWithReason(AlertCode code, const char *severity, const char *message, const char *reason);
};

extern DevicePlugin Device;
