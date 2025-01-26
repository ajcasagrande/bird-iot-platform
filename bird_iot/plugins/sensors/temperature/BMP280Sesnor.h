#pragma once

#include "sdkconfig.h"

#if CONFIG_ENABLE_BMP280_SENSOR

#include "TempSensor.h"
#include <Adafruit_BMP280.h>

class BMP280Sensor : public TempSensor {
private:
  uint8_t _address;
  Adafruit_BMP280 *bmp;
public:
  explicit BMP280Sensor(uint8_t address);

  bool setup() override;
//  bool start() override;
  void poll() override;
  bool hasHumiditySensor() override { return false; }
};

#endif // CONFIG_ENABLE_BMP280_SENSOR
