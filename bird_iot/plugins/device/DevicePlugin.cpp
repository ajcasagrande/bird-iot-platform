#include "DevicePlugin.h"

#include "include/version.h"
#include <esp32/rom/rtc.h>
#include <esp_task_wdt.h>
#include <rtos/xprintf.h>
#include <esp_private/system_internal.h>
#include "include/rtos.h"
#include "WebsocketWrapper.h"

DevicePlugin Device;

static const char* TAG = "Device";

void DevicePlugin::die(const char* reason, birdiot_reset_reason_t hint, uint32_t wait, bool error) {
  sendAlertWithReason(ALERT_SHUTTING_DOWN, reason);
  if (error) {
    LOGW(TAG, "DIE! Reason: " << reason);
  } else {
    LOGI(TAG, "Rebooting. Reason: " << reason);
  }

  while (wait > 0) {
    if (error) {
      LOGW(TAG, "Rebooting in " << wait << " ms...");
    } else {
      LOGI(TAG, "Rebooting in " << wait << " ms...");
    }
    taskDELAY(250);
    wait -= 250;
  }
  LOGW(TAG, "Rebooting..");
  WebsocketWrapper::disconnectAll();
  Mqtt.disconnect();

#if CONFIG_USE_ESP_RESTART
  Prefs.setResetReason((uint8_t) hint);
  esp_restart();
  // trip WDT if esp_restart fails
  taskDELAY(1000);
#endif

  hard_reset(hint);
}

void DevicePlugin::hard_reset(birdiot_reset_reason_t hint) {
  Prefs.setResetReason((uint8_t) hint);
  esp_reset_reason_set_hint((esp_reset_reason_t) hint);
  // todo:
  esp_restart_noos();
  // abort();
}

bool DevicePlugin::sendStatus(const char* status) {
  LOGI(TAG, "Sending status: " << status);
  currentStatus = status;

  const size_t capacity = JSON_OBJECT_SIZE(7);
  DynamicJsonDocument doc(capacity);
  doc["status"] = status;
  doc["millis"] = millis64();
  doc["ip"] = (const char*)WifiDriver::getIpAddress().c_str();
  doc["version"] = SOFTWARE_VERSION;
  doc["revision"] = SOFTWARE_REVISION;
  doc["vcc"] = readVcc();
  doc["env"] = CONFIG_BIRD_IOT_ENV;

  return Mqtt.publish(Mqtt.topics.status, doc);
}

bool DevicePlugin::sendAlertWithReason(AlertCode code, const char* severity, const char* message, const char* reason) {
  return sendAlert(code, severity, message, JSON_OBJECT_SIZE(1), [reason](JsonObject optional) {
    optional["reason"] = reason;
  });
}

bool DevicePlugin::sendAlert(AlertCode code, const char* severity, const char* message, size_t extraCapacity, const std::function<void(JsonObject)>& optionalLambda) {
  // send equivalent status first
  sendStatus(getStatusByAlert(code));

  LOGI(TAG, "Sending alert, severity: " << severity << ", code: " << code << ", message: " << message);
  const size_t capacity = JSON_OBJECT_SIZE(5) + extraCapacity;
  DynamicJsonDocument doc(capacity);
  doc["millis"] = millis64();
  doc["severity"] = severity;
  doc["code"] = (int)code;
  doc["message"] = message;
  if (optionalLambda != nullptr) {
    optionalLambda(doc.createNestedObject("optional"));
  }

  return Mqtt.publish(Mqtt.topics.alert, doc);
}

void DevicePlugin::onMqttConnected() {
  Mqtt.subscribe(DEVICE_BROADCAST_MQTT_TOPIC);
  Mqtt.subscribe(DEVICE_CONTROL_MQTT_TOPIC);

  if (!sentBootInfo) {
    sentBootInfo = sendBootInfo();
  }
  if (!sentCpuInfo) {
    sentCpuInfo = sendCpuInfo();
  }
}

bool DevicePlugin::handleMqttMessage(const char *topic, const int id, const char *cmd, const JsonDocument& json) {
  if (strcmp(DEVICE_BROADCAST_MQTT_TOPIC, topic) != 0
        && strcmp(DEVICE_CONTROL_MQTT_TOPIC, topic) != 0) {
    return false;
  }

  if (strcmp(cmd, "reboot") == 0) {
    die("reboot requested", RST_RESET_BY_COMMAND);
  } else if (strcmp(cmd, "status") == 0) {
    sendStatus(currentStatus);
  } else {
    LOGI(TAG, "unknown command");
    return false;
  }

  Mqtt.respondTrue(id);
  return true;
}

bool DevicePlugin::sendBootInfo() {
  LOGV(TAG, "sending boot info");

  const size_t capacity = JSON_OBJECT_SIZE(2);
  DynamicJsonDocument doc(capacity);
  const char* reason = getEspResetReason();

  doc["code"] = (int)esp_reset_reason();
  doc["reason"] = reason;

  Device.sendAlertWithReason(ALERT_POWER_ON, reason);

  return Mqtt.publish(Mqtt.topics.device_info_boot, doc);
}

bool DevicePlugin::sendCpuInfo() {
  LOGV(TAG, "sending cpu and memory info");

  const size_t capacity = JSON_OBJECT_SIZE(3);
  DynamicJsonDocument doc(capacity);

  esp_chip_info_t chip_info;
  esp_chip_info(&chip_info);

  doc["mhz"] = CONFIG_ESP32_DEFAULT_CPU_FREQ_MHZ;
  doc["cores"] = chip_info.cores;
  char rev[5];
  xsnprintf(rev, 5, "0x%02X", chip_info.revision);
  doc["rev"] = (const char*)rev;

  return Mqtt.publish(Mqtt.topics.device_info_cpu, doc);
}

const char* DevicePlugin::getStatusByAlert(AlertCode code) {
  switch (code) {
    case POWER_ON:
      return "power_on";
    case MQTT_CONNECTED:
      return "online";
    case OTA_VERIFIED:
      return "ota_verified";
    case SHUTTING_DOWN:
      return "shutting_down";
    case OTA_STARTED:
      return "ota_in_progress";
    case OTA_ERROR:
      return "ota_error";
    case OTA_INCOMPLETE:
      return "ota_incomplete";
    case OTA_COMPLETE:
      return "ota_complete";
    case OTA_ROLLBACK:
      return "ota_rollback";
    case BLE_CONNECTED:
      return "ble_connected";
    case BLE_DISCONNECTED:
      return "ble_disconnected";
    case BLE_INIT_FAILURE:
      return "ble_init_failure";
  }
  return "unknown";
}
