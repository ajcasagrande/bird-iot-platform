#include "BaseSensor.h"

static void _poll(BaseSensor *plugin) {
  plugin->poll();
}

static void _publish(BaseSensor *plugin) {
  plugin->publishData();
}

BaseSensor::BaseSensor(const std::string& name, const std::string& sensorName)
      : IotPlugin(name), sensorName(sensorName) {
  pollTask = new Task<BaseSensor>(sensorName + " Poll", this, _poll);
  publishTask = new Task<BaseSensor>(sensorName + " Publish", this, _publish);
}

bool BaseSensor::start() {
  return pollTask->start()
          && publishTask->start();
}
