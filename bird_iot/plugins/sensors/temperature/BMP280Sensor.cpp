#include "BMP280Sesnor.h"

#if CONFIG_ENABLE_BMP280_SENSOR

#include "i2cDriver.h"

static const char* TAG = "BMP280";

BMP280Sensor::BMP280Sensor(uint8_t address) : TempSensor("BMP280"), _address(address) {
  bmp = new Adafruit_BMP280();
}

bool BMP280Sensor::setup() {
  bool res = true;
  TRY_LOCK(i2cDriver,
    if (!bmp->begin(_address)) {
      res = false;
    }
  , res = false;);

  if (!res) {
    return false;
  }

  /* Default settings from datasheet. */
  bmp->setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                   Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                   Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                   Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                   Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

  i2cDriver.unlock();
  return TempSensor::setup();
}

void BMP280Sensor::poll() {
  i2cDriver.lock();
  float c = bmp->readTemperature();
  addTempValue(ctof(c));

  float p = bmp->readPressure();
  LOGI(TAG, "pressure: " << p);
  float a = bmp->readAltitude(1013.25);  // todo overwrite sealevelpa

  LOGI(TAG, "altitude: " << a);

  i2cDriver.unlock();

  // todo insert pressure and altitude
}

#endif // CONFIG_ENABLE_BMP280_SENSOR
