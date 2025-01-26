#pragma once
#include "sdkconfig.h"
#include "common.h"

class BaseSensor : public IotPlugin {
public:
  std::string sensorName;

  explicit BaseSensor(const std::string& name, const std::string& sensorName);

  bool start() override;

  virtual void poll() = 0;
  virtual void publishData() = 0;
  virtual bool setup() override = 0;

protected:
  Task<BaseSensor> *pollTask;
  Task<BaseSensor> *publishTask;

};
