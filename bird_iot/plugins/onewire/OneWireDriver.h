#pragma once
#include "sdkconfig.h"

#if CONFIG_ENABLE_ONE_WIRE_DRIVER

#include <OneWire.h>
#include <DallasTemperature.h>
#include "common.h"

typedef uint8_t OneWireAddress[8];

class OneWirePlugin : public IotPlugin {
private:
  uint8_t _pin;

public:
  OneWirePlugin();

  OneWire *oneWire;
  DallasTemperature *dallas;
  std::vector<OneWireAddress> devices;

  void setPin(uint8_t pin) { _pin = pin; }

  bool setup() override;

  bool autoRegisterDevices();
  bool scanDevices();

//  bool start() override;
//  void onWifiConnected() override;
//  void onWifiDisconnected() override;
//  void onMqttConnected() override;
//  void onMqttDisconnected() override;
//  bool handleMqttMessage(const char *topic, int id, const char *cmd, const JsonDocument& json) override;
//  bool handleCommand(std::string cmd) override;
#if CONFIG_ENABLE_I2C_OLED_DISPLAY_PLUGIN
//  void addFramesAndOverlays() override;
#endif
};

extern OneWirePlugin OneWireDriver;

#endif // CONFIG_ENABLE_ONE_WIRE_DRIVER
