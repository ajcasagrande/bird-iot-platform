#pragma once

#include "sdkconfig.h"

#if CONFIG_ENABLE_I2C_DRIVER

#include <vector>
#include "IotPlugin.h"
#include "tasks/TaskClass.h"
#include "Lockable.h"

class I2CDriver : public IotPlugin, public RecursiveLockable {
private:
  bool sentScan = false;
  bool initialized = false;
  uint8_t _sda, _scl;
  void registerI2CPlugin(IotPlugin *plugin, int address);
  esp_err_t i2c_master_driver_initialize();

public:
  void scan(std::vector<uint8_t> &found);
  void scanIDF(std::vector<uint8_t> &found);
  void autoRegister();
  void scanAndPublish();
  void setPins(uint8_t sda, uint8_t scl) { _sda = sda; _scl = scl; }

  I2CDriver(uint8_t sda, uint8_t scl) : IotPlugin("i2c Driver"), _sda(sda), _scl(scl) { }
  bool setup() override;
//  bool start() override;
  void onMqttConnected() override;
  bool handleMqttMessage(const char *topic, int id, const char *cmd, const JsonDocument& json) override;
  bool handleCommand(const std::string& cmd) override;
};

extern I2CDriver i2cDriver;

#endif // CONFIG_ENABLE_I2C_DRIVER
