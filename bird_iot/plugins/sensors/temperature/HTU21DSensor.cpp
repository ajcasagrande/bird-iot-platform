#include "HTU21DSensor.h"

#if CONFIG_ENABLE_HTU21D_SENSOR

#include "i2cDriver.h"

static const char *TAG = "HTU21D";

bool HTU21DSensor::setup() {
  LOGI(TAG, "HTU21D init");
  TRY_LOCK(i2cDriver, htu.begin(), return false;)
  return TempSensor::setup();
}

void HTU21DSensor::poll() {
  float h, c;
  TRY_LOCK(i2cDriver,
    h = htu.readHumidity();
    c = htu.readTemperature();
  , markInvalidData(); return;)

  addValues(ctof(c), h);
}

#endif // CONFIG_ENABLE_HTU21D_SENSOR
