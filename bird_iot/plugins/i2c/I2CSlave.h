#pragma once
#include "sdkconfig.h"

#if CONFIG_ENABLE_I2C_SLAVE

#include "common.h"
#include "SpektrumDevice.h"

#define SPEKTRUM_PACKET_SIZE (16)
#define I2C_SLAVE_TX_BUF_LEN (2 * 512)              /*!< I2C slave tx buffer size */
#define I2C_SLAVE_RX_BUF_LEN (2 * 512)              /*!< I2C slave rx buffer size */

class I2CSlave : public IotPlugin {
private:
  bool initialized = false;
  uint8_t _sda, _scl;
  uint8_t _addr;
//  uint8_t _buff[I2C_SLAVE_RX_BUF_LEN];
//  esp_err_t i2c_slave_driver_initialize();
  SpektrumDevice device;

public:
  I2CSlave(uint8_t sda, uint8_t scl, uint8_t addr);

  bool setup() override;
  bool start() override;
  void execute();

//  void onWifiConnected() override;
//  void onWifiDisconnected() override;
//  void onMqttConnected() override;
//  void onMqttDisconnected() override;
//  bool handleMqttMessage(const char *topic, int id, const char *cmd, const JsonDocument& json) override;
//  bool handleCommand(const std::string& cmd) override;
#if ENABLE_I2C_OLED_DISPLAY_PLUGIN
//  void addFramesAndOverlays() override;
#endif

private:
  Task<I2CSlave> *task;

};

#endif // CONFIG_ENABLE_I2C_SLAVE
