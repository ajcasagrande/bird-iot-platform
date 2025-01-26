#include "ExampleTempSensor.h"

#if CONFIG_ENABLE_EXAMPLE_TEMP_SENSOR

ExampleTempSensor::ExampleTempSensor(byte address) : TempSensor("Example Temp Sensor"), _address(address) {
  // todo
}

void ExampleTempSensor::poll() {
  // TODO
  if (INVALID) {
    markInvalidData();
    return;
  }
  addValues(f, h);
}

#endif // CONFIG_ENABLE_EXAMPLE_TEMP_SENSOR
