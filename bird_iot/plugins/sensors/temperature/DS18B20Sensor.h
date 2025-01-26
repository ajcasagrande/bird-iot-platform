#pragma once

#include "sdkconfig.h"

#if CONFIG_ENABLE_DS18B20_SENSOR_PLUGIN

#include <OneWire.h>
#include <DallasTemperature.h>

#include "TempSensor.h"

class DS18B20Sensor : public TempSensor {
public:
  explicit DS18B20Sensor(int index);

  int index;

  bool setup() override;
//  bool start() override;
  void poll() override;
  bool hasHumiditySensor() override;
};

#endif // CONFIG_ENABLE_DS18B20_SENSOR_PLUGIN
