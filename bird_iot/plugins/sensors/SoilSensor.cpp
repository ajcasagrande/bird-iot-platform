#include "SoilSensor.h"

#if CONFIG_ENABLE_SOIL_SENSOR

static const char* TAG = "Soil Sensor";

SoilSensor::SoilSensor(gpio_num_t pin)
    : BaseSensor("Soil Sensor", "Moisture"), pin(pin), stats("Moisture") {

}

bool SoilSensor::setup() {
  pinMode(pin, INPUT);

  return pollTask->configure(CONFIG_SOIL_SENSOR_POLL_INTERVAL, _1p25, MEDIUM_PRIORITY)
          && publishTask->configure(CONFIG_SOIL_SENSOR_PUBLISH_INTERVAL, _1p5, MEDIUM_PRIORITY);
}

void SoilSensor::markInvalidData() {
  LOGE(TAG, "Error, invalid moisture data. Check connection to pin " << pin << ".");
  ++stats.invalidSamples;
}

// approximate moisture levels for the sensor reading
// 0 to 20% -- dry soil
// 20 - 60% -- humid soil
// 60+ %    -- in water
void SoilSensor::poll() {
  uint16_t rawValue = analogRead(pin);
  if (rawValue <= minRawMoistureValue) {
    markInvalidData();
    return;
  }

  float value = (1.f - ((float)rawValue / 4095.f)) * 100.f;
  stats.addValue(value);
  if (stats.changed_by >= 1.0) {
    LOGD(TAG, rawValue << " (" << stats.current << "%)");
  }
}

void SoilSensor::publishData() {
  LOGD(TAG, "publishData called");

  if (stats.samples == 0.0) {
    LOGW(TAG, "no moisture data to publish");
    return;
  }

  const size_t capacity = JSON_OBJECT_SIZE(4);
  DynamicJsonDocument doc(capacity);
  doc["name"] = "Soil Sensor v2.0";
  doc["type"] = "moisture";
  doc["moisture"] = stats.getAverage(2);
  doc["unit"] = "%";

  Mqtt.publish(Mqtt.topics.sensors, doc);
  stats.reset();
}

//  void SoilSensor::onWifiConnected() { }
//  void SoilSensor::onWifiDisconnected() { }
//  void SoilSensor::onMqttConnected() { }
//  void SoilSensor::onMqttDisconnected() { }
//  bool SoilSensor::handleMqttMessage(const char *topic, int id, const char *cmd, const JsonDocument& json) {
//   return false; // false means not handled 
// }
//  bool SoilSensor::handleCommand(const std::string& cmd) {
//   return false; // false means not handled 
// }
#if ENABLE_I2C_OLED_DISPLAY_PLUGIN
//  void SoilSensor::addFramesAndOverlays() { }
#endif

#endif // CONFIG_ENABLE_SOIL_SENSOR
