#include "ESP32TempSensor.h"
#if CONFIG_ENABLE_ESP32_INTERNAL_TEMP_SENSOR

extern "C" uint8_t temprature_sens_read();

ESP32TempSensor::ESP32TempSensor() : TempSensor("ESP32") {
  unit = "?";
  _readInterval = 5000;
  _publishInterval = 60000;
}

void ESP32TempSensor::poll() {
  addTempValue(temprature_sens_read());
}

#endif // CONFIG_ENABLE_ESP32_INTERNAL_TEMP_SENSOR
