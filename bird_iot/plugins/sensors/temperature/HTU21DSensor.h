#pragma once

#include "sdkconfig.h"

#if CONFIG_ENABLE_HTU21D_SENSOR

#include "TempSensor.h"
#ifdef HTU21D_ADDRESS
#undef HTU21D_ADDRESS
#endif
#include <SparkFunHTU21D.h>

class HTU21DSensor : public TempSensor {
private:
  HTU21D htu;

public:
  HTU21DSensor() : TempSensor("HTU21D") { }

  bool setup() override;
//  bool start() override;
  void poll() override;
  bool hasHumiditySensor() override { return true; }
};

#endif // CONFIG_ENABLE_HTU21D_SENSOR
