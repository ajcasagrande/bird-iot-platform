#include "RFTransmitPlugin.h"

#if CONFIG_ENABLE_RF_TRANSMIT_PLUGIN

#include "include/common.h"

static const char* TAG = "RF Transmit";

RFTransmitPlugin::RFTransmitPlugin(uint freq, uint8_t txPin, uint8_t repeatTransmit)
    : IotPlugin("RF Transmit Plugin") {
  this->freq = freq;
  subscribeTopic.concat(freq);
  this->txPin = txPin;
  this->repeatTransmit = repeatTransmit;
}

bool RFTransmitPlugin::setup() {
  REQUIRE_VALID_OUTPUT_PIN(txPin);

  pinMode(txPin, OUTPUT);
  digitalWrite(txPin, LOW);
  rf.enableTransmit(txPin);
  rf.setRepeatTransmit(repeatTransmit);
  return true;
}

void RFTransmitPlugin::onMqttConnected() {
  Mqtt.subscribe(subscribeTopic.c_str());
}

void RFTransmitPlugin::transmit(uint64_t code, int bits, int protocol, int pulseLength, uint8_t syncHigh, uint8_t syncLow) {
  rf.setProtocol(protocol);
  if (pulseLength != 0) {
    rf.setPulseLength(pulseLength);
  }
  if (syncHigh != 1 || syncLow != 1) {
    rf.setSyncFactor(syncHigh, syncLow);
  }
  LOGI(TAG, "RF Transmit: " <<code<< ", bits: " <<bits<< ", protocol: " <<protocol<< ", pulse: " << pulseLength);
  rf.send(code, bits);
  // just in case, reset the pin
  // todo: what about when the code is inverted? should we still do this? I think yeah, otherwise a constant HIGH
  //       would generate a ton of interference on the channel
  digitalWrite(txPin, LOW);
}

bool RFTransmitPlugin::handleMqttMessage(const char *topic, const int id, const char *cmd, const JsonDocument& json) {
  if (!String(topic).equals(subscribeTopic)) {
    return false;
  }

  if (strcmp(cmd, "send") == 0) {
    int pulse;
    uint8_t syncHigh, syncLow;
    getJsonProperty(uint64_t code, "c");
    getJsonProperty(int bits, "b");
    getJsonProperty(int protocol, "p");
    getOrDefaultJsonProperty(pulse, "u", 0);
    // todo: crash when key does not exist -- anthony @ 8/6/22 Does this still exist?
    getOrDefaultJsonProperty(syncHigh, "sh", 1);
    getOrDefaultJsonProperty(syncLow, "sl", 1);
    transmit(code, bits, protocol, pulse, syncHigh, syncLow);
  } else {
    LOGI(TAG, "unknown command");
    return false;
  }

  Mqtt.respondTrue(id);
  return true;
}

#endif // CONFIG_ENABLE_RF_TRANSMIT_PLUGIN
