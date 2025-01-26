#include "HunterFanPlugin.h"
#include "include/rtos.h"

#if CONFIG_ENABLE_HUNTER_FAN_PLUGIN

static const char* TAG = "Hunter Fan";

HunterFanPlugin::HunterFanPlugin(int pin, int repeats) 
    : IotPlugin("Hunter Fan Plugin") {
  this->pin = pin;
  this->repeats = repeats;
}

bool HunterFanPlugin::setup() {
  REQUIRE_VALID_OUTPUT_PIN(pin);

  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
  return true;
}

void HunterFanPlugin::onMqttConnected() {
  Mqtt.subscribe(HUNTER_FAN_MQTT_TOPIC);
}

void HunterFanPlugin::sendHunterFanCode(uint64_t code, const int bits) {
//  setStatusColor(ORANGE);

  LOGI(TAG, "Hunter Fan Code: ...");
  for (int i=0; i < repeats; i++) {
    // initial pulse
    digitalWrite(pin, HIGH);
    delayMicroseconds(6437);

    bool low = true;
    int bit = 0;

    cli();  // this turns off any background interrupts
    for (int j=bits-1; j >= 0; j--) {
      digitalWrite(pin, low ? LOW : HIGH);
      bit = code >> j & 1;
      if (bit == 0) {
        delayMicroseconds(350);
      } else if (bit == 1) {
        delayMicroseconds(700);
      } else {
        LOGI(TAG, "error, improper code");
        break;
      }
      low = !low;
    }
    sei();  // this turns them back on

    // end with some blank space
    digitalWrite(pin, LOW);
    taskDELAY(30);
  }
//  setStatusColor(ONLINE);
}

// doesn't check for sign
// doesn't check for base-prefix
uint64_t strtoll(const char *nptr, int base) {
  uint64_t val = 0;

  for (; *nptr; nptr++) {
    int v = *nptr;
    if ('0' <= v && v <= '9') {
      v -= '0';
    } else if ('A' <= v && v <= 'Z') {
      v -= 'A' - 10;
    } else if ('a' <= v && v <= 'z') {
      v -= 'a' - 10;
    } else {
      break;
    }
    if (v >= base) {
      break;
    }
    val = val * base + v;
  }

  return val;
}

bool HunterFanPlugin::handleMqttMessage(const char *topic, const int id, const char *cmd, const JsonDocument& json) {
  if (strcmp(topic, HUNTER_FAN_MQTT_TOPIC) != 0) {
    return false;
  }

  if (strcmp(cmd, "send") == 0) {
    getJsonProperty(const char* code36, "c");
    uint64_t code = strtoll(code36, 36);
    getJsonProperty(const int bits, "b");
    sendHunterFanCode(code, bits);
  } else {
    LOGI(TAG, "unknown command");
    return false;
  }

  Mqtt.respondTrue(id);
  return true;
}

#endif // CONFIG_ENABLE_HUNTER_FAN_PLUGIN
