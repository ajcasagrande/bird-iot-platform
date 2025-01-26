#include "HDC1008Sensor.h"
#include "i2cDriver.h"

#if CONFIG_ENABLE_HDC1008_SENSOR

static const char* TAG = "HDC1008";

HDC1008Sensor::HDC1008Sensor(int address) : TempSensor("HDC1008") {
  this->address = address;
}

bool HDC1008Sensor::checkInit() {
  bool rval = hdc.begin(address);
  i2cDriver.unlock();
  return rval;
}

bool HDC1008Sensor::setup() {
  LOGI(TAG, "HDC1008 init");
  if (!checkInit()) {
    LOGW(TAG, "Couldn't find HDC1008!");
    return false;
  }
  return TempSensor::setup();
}

void HDC1008Sensor::poll() {
  i2cDriver.lock();
  float c, f, h;
  c = hdc.readTemperature();
  f = ctof(c);
  h = hdc.readHumidity();

  if (h > 99.9) {
    this->markInvalidData();
    i2cDriver.unlock();
    return;
  }
  this->addValues(f, h);
  i2cDriver.unlock();
}

#endif // CONFIG_ENABLE_HDC1008_SENSOR
