#include "DHTSensor.h"

#if CONFIG_ENABLE_DHT_TEMP_SENSOR_PLUGIN

#include "include/common.h"

static const char* TAG = "DHT";

const char* internalSensorName(int model) {
  char* name = (char*)malloc(10);
  sprintf(name, "DHT%d", model);
  return (const char*)name;
}

DHTSensor::DHTSensor(int pin, int model)
    : TempSensor(internalSensorName(model)) {
  this->pin = pin;
  this->model = model;
}

bool DHTSensor::setup() {
  LOGI(TAG, "init");
  dht = new DHT(pin, model);
  dht->begin();
  return TempSensor::setup();
}

bool DHTSensor::hasHumiditySensor() {
  return true;
}

void DHTSensor::poll() {
  float h = dht->readHumidity();
  float c = dht->readTemperature();

  if (isnan(h) || isnan(c)) {
    markInvalidData();
    return;
  }

  addValues(ctof(c), h);
}

#endif // CONFIG_ENABLE_DHT_TEMP_SENSOR_PLUGIN
