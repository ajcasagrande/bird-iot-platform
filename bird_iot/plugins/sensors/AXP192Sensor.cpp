#include "AXP192Sensor.h"

#if CONFIG_ENABLE_AXP192_SENSOR

#include "I2CDriver.h"

static const char* TAG = "AXP192";

AXP192SensorClass AXP192Sensor;

AXP192SensorClass::AXP192SensorClass() : IotPlugin("AXP192 Sensor") { }

bool AXP192SensorClass::setup() {
  bool res;
  TRY_LOCK(i2cDriver,
      res = axp192.begin();
  , return false;);
  configured = res;
  return res;
}

bool AXP192SensorClass::start() {
  TRY_LOCK(i2cDriver,
    LOGD(TAG,
        "temp: " << axp192.GetTempInAXP192() <<
        ", vIn: " << axp192.GetVinVoltage() <<
        ", vBat: " << axp192.GetBatVoltage() <<
        ", vBus: " << axp192.GetVBusVoltage() <<
        ", vAPS: " << axp192.GetAPSVoltage());
  , return false;);
  return true;
}

double AXP192SensorClass::getVcc() {
  double v;
  TRY_LOCK(i2cDriver,
      v = axp192.GetVBusVoltage();
  , return 0.0;);
  return v;
}

//  void AXP192SensorClass::onWifiConnected() { }
//  void AXP192SensorClass::onWifiDisconnected() { }
//  void AXP192SensorClass::onMqttConnected() { }
//  void AXP192SensorClass::onMqttDisconnected() { }
//  bool AXP192SensorClass::handleMqttMessage(const char *topic, int id, const char *cmd, const JsonDocument& json) {
//   return false; // false means not handled 
// }
//  bool AXP192SensorClass::handleCommand(const std::string& cmd) {
//   return false; // false means not handled
// }
#if ENABLE_I2C_OLED_DISPLAY_PLUGIN
//  void AXP192SensorClass::addFramesAndOverlays() { }
#endif

#endif // CONFIG_ENABLE_AXP192_SENSOR
