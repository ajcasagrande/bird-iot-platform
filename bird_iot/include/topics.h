#pragma once

#include "util/helpers.h"
#include <string>

//// ------ MQTT TOPICS ------
// --- SUBSCRIBE ---
#define GARAGE_MQTT_TOPIC "iot/garage"
#define IR_MQTT_TOPIC "iot/ir"
#define I2C_MQTT_TOPIC "iot/i2c"
#define RF_MQTT_TOPIC "iot/rf"
#define RSSI_MQTT_TOPIC "iot/rssi"
#define NEOPIXEL_MQTT_TOPIC "iot/neopixel"
#define HUNTER_FAN_MQTT_TOPIC "iot/fan/hunter"
#define DEVICE_BROADCAST_MQTT_TOPIC "iot/devices"
#define DEVICE_CONTROL_MQTT_TOPIC "iot/control"
#define OTA_MQTT_TOPIC_BASE "iot/ota/"


// #define topic2(tp1, tp2) const std::string tp1##_##tp2 = #tp1 "/" #tp2
#define topic2(tp1, tp2) const char* tp1##_##tp2 = #tp1 "/" #tp2
#define topic3(tp1, tp2, tp3) const std::string tp1##_##tp2##_##tp3 = #tp1 "/" #tp2 "/" #tp3
#define device_topic(tp) const std::string tp = std::string("iot/" #tp "/") + deviceId()
#define device_topic2(tp1, tp2) const std::string tp1##_##tp2 = std::string("iot/" #tp1 "/" #tp2 "/") + deviceId()
#define device_topic3(tp1, tp2, tp3) const std::string tp1##_##tp2##_##tp3 = std::string("iot/" #tp1 "/" #tp2 "/" #tp3 "/") + deviceId()

class TopicsClass {
public:
  // publish
  device_topic(alert);
  device_topic(temp);
  device_topic(sensors);
  device_topic(rssi);
  device_topic2(rf, data);
  device_topic2(i2c, scan);
  device_topic(garage);
  device_topic2(status, lost);
  device_topic(response);
  device_topic(status);
  device_topic3(device, info, boot);
  device_topic3(device, info, cpu);
  device_topic3(device, info, board);
  device_topic2(sketch, info);
  device_topic2(wifi, scan);

  //subscribe
  device_topic(firmware);
  device_topic(command);
  device_topic2(media, control);
};
