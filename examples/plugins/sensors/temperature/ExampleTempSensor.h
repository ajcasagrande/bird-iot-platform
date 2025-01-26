#pragma once

#include "sdkconfig.h"

#if CONFIG_ENABLE_EXAMPLE_TEMP_SENSOR

#include "TempSensor.h"
#include <ExampleTemp.h>

class ExampleTempSensor : public TempSensor {
private:
  byte _address;
  ExampleTemp *sensor;
public:
  ExampleTempSensor(byte address);
  bool setup() override;
//  bool start() override;
  void poll() override;
  bool hasHumiditySensor() override { return true; }
};

#endif // CONFIG_ENABLE_EXAMPLE_TEMP_SENSOR
