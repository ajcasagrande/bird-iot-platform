#pragma once
#include "sdkconfig.h"

#if CONFIG_ENABLE_ESP32_INTERNAL_TEMP_SENSOR

#include "TempSensor.h"

class ESP32TempSensor : public TempSensor {
public:
  ESP32TempSensor();
  void poll() override;
  bool hasHumiditySensor() override { return false; }
};

#endif // CONFIG_ENABLE_ESP32_INTERNAL_TEMP_SENSOR
