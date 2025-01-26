#include "LM75ASensor.h"

#if CONFIG_ENABLE_LM75A_SENSOR

#include <LM75A.h>
#include "i2cDriver.h"

static const char *TAG = "LM75A";

LM75ASensor::LM75ASensor(int address)
    : TempSensor("LM75A") {
  this->address = address;
}

bool LM75ASensor::setup() {
  bool res;
  TRY_LOCK(i2cDriver,
      LOGI(TAG, "LM75A init");
      lm75a = new LM75A(address);
      res = TempSensor::setup();
  , return false;)

  return res;
}

void LM75ASensor::poll() {
  float c;
  TRY_LOCK(i2cDriver, c = lm75a->getTemperatureInDegrees(), markInvalidData(); return;)

  if (c == INVALID_LM75A_TEMPERATURE) {
    markInvalidData();
    return;
  }

  float f = ctof(c);
  addTempValue(f);
}

#endif // CONFIG_ENABLE_LM75A_SENSOR
