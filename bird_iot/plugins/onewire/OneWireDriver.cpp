#include "OneWireDriver.h"

#if CONFIG_ENABLE_ONE_WIRE_DRIVER

static const char* TAG = "OneWire";

OneWirePlugin OneWireDriver;

OneWirePlugin::OneWirePlugin() : IotPlugin("OneWire Driver") {
  oneWire = new OneWire();
  dallas = new DallasTemperature(oneWire);
}

bool OneWirePlugin::setup() {
  if (!GPIO_IS_VALID_GPIO(_pin)) {
    LOGE(TAG, "Invalid pin (" << _pin << ") specific for one wire!");
    return false;
  }

  oneWire->begin(_pin);
  dallas->begin();
  return true;
}

bool OneWirePlugin::autoRegisterDevices() {
  return true;
}

bool OneWirePlugin::scanDevices() {
  return true;
}

//  bool OneWirePlugin::start() {
//   return true;
// }
//  void OneWirePlugin::onWifiConnected() { }
//  void OneWirePlugin::onWifiDisconnected() { }
//  void OneWirePlugin::onMqttConnected() { }
//  void OneWirePlugin::onMqttDisconnected() { }
//  bool OneWirePlugin::handleMqttMessage(const char *topic, int id, const char *cmd, const JsonDocument& json) {
//   return false; // false means not handled 
// }
//  bool OneWirePlugin::handleCommand(std::string cmd) {
//   return false; // false means not handled
// }
#if ENABLE_I2C_OLED_DISPLAY_PLUGIN
//  void OneWirePlugin::addFramesAndOverlays() { }
#endif

#endif // CONFIG_ENABLE_ONE_WIRE_DRIVER
