#pragma once

#include "sdkconfig.h"

#if CONFIG_ENABLE_LM75A_SENSOR

#include <LM75A.h>

#include "TempSensor.h"

/**
 * The LM75A provides 9-bit digital temperature Bus readings with
 * an accuracy of ±2°C from –25°C to 100°C and ±3°C over –55°C to 125°C.
 */
class LM75ASensor : public TempSensor {
private:
  int address;
  LM75A* lm75a;
public:
  explicit LM75ASensor(int);

  bool setup() override;
//  bool start() override;
  void poll() override;
  bool hasHumiditySensor() override { return false; }
};

#endif // CONFIG_ENABLE_LM75A_SENSOR
