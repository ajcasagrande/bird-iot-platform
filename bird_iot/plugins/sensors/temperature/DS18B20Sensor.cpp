#include "DS18B20Sensor.h"

#if CONFIG_ENABLE_DS18B20_SENSOR_PLUGIN

#include "OneWireDriver.h"
#include <DallasTemperature.h>

static const char* TAG = "DS18B20";

DS18B20Sensor::DS18B20Sensor(int index)
    : TempSensor("DS18B20"), index(index) {
}

bool DS18B20Sensor::setup() {
  LOGI(TAG, "DS18B20 init");
  LOGI(TAG, "Found " << OneWireDriver.dallas->getDeviceCount() << " one-wire devices on the bus!");
  LOGI(TAG, OneWireDriver.dallas->getDS18Count() << " are DS18 devices!");
  return TempSensor::setup();
}

bool DS18B20Sensor::hasHumiditySensor() {
  return false;
}

void DS18B20Sensor::poll() {
  OneWireDriver.dallas->requestTemperatures();
  float c = OneWireDriver.dallas->getTempCByIndex(index);
  if (c == DEVICE_DISCONNECTED_C) {
    markInvalidData();
    return;
  }
  float f = ctof(c);
  addTempValue(f);
}

#endif // CONFIG_ENABLE_DS18B20_SENSOR_PLUGIN
