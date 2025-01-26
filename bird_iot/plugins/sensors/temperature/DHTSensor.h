#pragma once

#include "sdkconfig.h"

#if CONFIG_ENABLE_DHT_TEMP_SENSOR_PLUGIN

#include "TempSensor.h"
#include <DHT.h>

class DHTSensor : public TempSensor {
private:
  int pin;
  int model;
  DHT *dht;
public:
  DHTSensor(int pin, int model);
  bool setup() override;
//  bool start() override;
  void poll() override;
  bool hasHumiditySensor() override;
};

#endif // CONFIG_ENABLE_DHT_TEMP_SENSOR_PLUGIN
