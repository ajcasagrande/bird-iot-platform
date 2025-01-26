#pragma once

#include "sdkconfig.h"

#if CONFIG_ENABLE_MCP9808_SENSOR

#include <Adafruit_MCP9808.h>

#include "TempSensor.h"

class MCP9808Sensor : public TempSensor {
private:
  int address;
  Adafruit_MCP9808 mcp;
public:
  explicit MCP9808Sensor(int);

  bool setup() override;
//  bool start() override;
  void poll() override;
  bool hasHumiditySensor() override { return false; }
};

#endif // CONFIG_ENABLE_MCP9808_SENSOR
