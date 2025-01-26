#pragma once

#include "sdkconfig.h"

#if CONFIG_ENABLE_RF_TRANSMIT_PLUGIN

#include <RCSwitch.h>

#include "include/topics.h"
#include "IotPlugin.h"

class RFTransmitPlugin : public IotPlugin {
private:
  uint freq;
  uint8_t txPin;
  uint8_t repeatTransmit;
  RCSwitch rf = RCSwitch();
  void transmit(uint64_t code, int bits, int protocol, int pulseLength, uint8_t syncHigh, uint8_t syncLow);
  String subscribeTopic = String(RF_MQTT_TOPIC);
public:
  // IotPlugin implementation
  RFTransmitPlugin(uint freq, uint8_t txPin, uint8_t repeatTransmit);
  bool setup() override;
//  bool start() override;
  void onMqttConnected() override;
  bool handleMqttMessage(const char *topic, int id, const char *cmd, const JsonDocument& json) override;
};

#endif // CONFIG_ENABLE_RF_TRANSMIT_PLUGIN
