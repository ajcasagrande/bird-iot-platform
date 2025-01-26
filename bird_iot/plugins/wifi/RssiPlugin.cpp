#include "RssiPlugin.h"
#if CONFIG_ENABLE_RSSI_STATS_PLUGIN

#include <esp_wifi.h>
#include "include/common.h"

RssiPlugin RssiStats;

static const char* TAG = "RSSI";

void _poll(RssiPlugin *plugin) {
  plugin->poll();
}

void _publishData(RssiPlugin *plugin) {
  plugin->publishData();
}

RssiPlugin::RssiPlugin() : IotPlugin("Rssi Stats Plugin") {
  pollTask = new Task<RssiPlugin>("RSSI Poll", this, _poll);
  publishTask = new Task<RssiPlugin>("RSSI Publish", this, _publishData);
}

bool RssiPlugin::setup() {
  return pollTask->configure(CONFIG_RSSI_SAMPLE_INTERVAL, _1p5, LOW_PRIORITY) &&
         publishTask->configure(CONFIG_RSSI_PUBLISH_INTERVAL, _1p25, MEDIUM_LOW_PRIORITY);
}

bool RssiPlugin::start() {
  return pollTask->start()
         && publishTask->start();
}

void RssiPlugin::poll() {
  if (esp_wifi_sta_get_ap_info(&info) != ESP_OK) {
    ++stats.invalidSamples;
    return;
  }

  stats.addValue(info.rssi);

  if (stats.changed) {
#if CONFIG_LOG_RSSI
    LOGD(TAG, info.rssi << " dBm");
#endif
#if CONFIG_ENABLE_I2C_LCD_CHARACTER_DISPLAY
//    char rssiStr[10];
//    sprintf(rssiStr, "%d dBm", info.rssi);
//    App.lcdPrint(0, 0, rssiStr);
#endif
  }
}

void RssiPlugin::publishData() {
  if (stats.samples == 0.0) {
    LOGW(TAG, "Error, no rssi data to publish");
    return;
  }

  const size_t capacity = JSON_OBJECT_SIZE(3);
  DynamicJsonDocument json(capacity);
  double avg = stats.getAverage(2);
  json["min"] = (int)stats.min;
  json["max"] = (int)stats.max;
  json["avg"] = avg;

  Mqtt.publish(Mqtt.topics.rssi, json);

  stats.reset();
}

void RssiPlugin::onMqttConnected() {
  Mqtt.subscribe(RSSI_MQTT_TOPIC);
}

bool RssiPlugin::handleMqttMessage(const char *topic, const int id, const char *cmd, const JsonDocument& json) {
  if (strcmp(RSSI_MQTT_TOPIC, topic) != 0) {
    return false;
  }

  if (strcmp(cmd, "stats") == 0) {
    publishData();
  } else {
    LOGW(TAG, "unknown command");
    return false;
  }

  Mqtt.respondTrue(id);
  return true;
}

bool RssiPlugin::handleCommand(const std::string& cmd) {
  if (cmd == "rssi") {
    LOGI(TAG, "current rssi: " << WiFi.RSSI());
    stats.getAverage(2);
    return true;
  }

  return false;
}

#endif // CONFIG_ENABLE_RSSI_STATS_PLUGIN
