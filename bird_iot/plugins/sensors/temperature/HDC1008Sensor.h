#pragma once

#include "sdkconfig.h"

#if CONFIG_ENABLE_HDC1008_SENSOR

#include "TempSensor.h"
#include <Adafruit_HDC1000.h>

class HDC1008Sensor : public TempSensor {
private:
  int address;
  Adafruit_HDC1000 hdc;
public:
  explicit HDC1008Sensor(int address);
  bool setup() override;
//  bool start() override;
  void poll() override;
  bool hasHumiditySensor() override { return true; }

  bool checkInit();
};

#endif // CONFIG_ENABLE_HDC1008_SENSOR
