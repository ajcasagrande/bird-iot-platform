#include "MCP9808Sensor.h"

#if CONFIG_ENABLE_MCP9808_SENSOR

#include "i2cDriver.h"

static const char *TAG = "MCP9808";

MCP9808Sensor::MCP9808Sensor(int address) : TempSensor("MCP9808") {
  this->address = address;
}

bool MCP9808Sensor::setup() {
  bool res;
  TRY_LOCK(i2cDriver,
    LOGI(TAG, "MCP9808 init");
    if (!mcp.begin(address)) {
      LOGW(TAG, "Couldn't find MCP9808!");
      res = false;
    } else {
      res = TempSensor::setup();
    }
  , return false;)
  return res;
}

void MCP9808Sensor::poll() {
  float c;
  TRY_LOCK(i2cDriver, c = mcp.readTempC(), markInvalidData(); return;)

  if (c > -0.07 && c < -0.05) {
    markInvalidData();
    return;
  }
  float f = ctof(c);
  addTempValue(f);
}

#endif // CONFIG_ENABLE_MCP9808_SENSOR
