#include "I2CSlave.h"
#if CONFIG_ENABLE_I2C_SLAVE

#include <driver/i2c.h>
#include "spektrum.h"
#include "SpektrumDevice.h"

static const char* TAG = "I2C Task";

static i2c_port_t i2c_slave_port = I2C_NUM_1;

static void _execute(I2CSlave *plugin) {
  plugin->execute();
}

I2CSlave::I2CSlave(uint8_t sda, uint8_t scl, uint8_t addr) : IotPlugin("I2C Slave"), _sda(sda), _scl(scl), _addr(addr) {
  task = new Task<I2CSlave>("I2C Slave", this, _execute);
}

bool I2CSlave::setup() {
//  i2c_slave_driver_initialize();
//  int size = i2c_slave_write_buffer(i2c_slave_port, tmpSpektrumData1, SPEKTRUM_PACKET_SIZE, 1000 / portTICK_RATE_MS);
//  LOGI(TAG, "Wrote " << size << " bytes from i2c slave");
  device.configure(i2c_slave_port, _sda, _scl, _addr);
  device.init();
  return task->configure(100, _2p5, MEDIUM_PRIORITY);
}
bool I2CSlave::start() {
  device.start();
  return task->start();
}

void I2CSlave::execute() {
  SPM_LOCK(device,
           device.data->gyro.gyroX++;
                device.data->gyro.gyroY++;
                device.data->gyro.gyroZ++;
                device.data->gyro.maxGyroX=999;
                device.data->gyro.maxGyroY=1023;
                device.data->gyro.maxGyroZ=1456;);

////    int size = i2c_slave_write_buffer(i2c_slave_port, tmpSpektrumData1, SPEKTRUM_PACKET_SIZE, 1000 / portTICK_RATE_MS);
//    if (size > 0) {
//      for (int i=2; i < SPEKTRUM_PACKET_SIZE; i++) {
//        tmpSpektrumData1[i]++;
//      }
//    }
//  device.lock()
}

//esp_err_t I2CSlave::i2c_slave_driver_initialize() {
//  auto *conf = new(i2c_config_t);
//  conf->mode = I2C_MODE_SLAVE;
//  conf->sda_io_num = gpio_num_t(_sda);
//  conf->sda_pullup_en = GPIO_PULLUP_ENABLE;
//  conf->scl_io_num = gpio_num_t(_scl);
//  conf->scl_pullup_en = GPIO_PULLUP_ENABLE;
//  conf->slave = {.addr_10bit_en = 0, .slave_addr = (uint16_t)(_addr & 0x7F)};
//  esp_err_t err = i2c_param_config(i2c_slave_port, conf);
//  if (err != ESP_OK) {
//      return err;
//  }
//  LOGI(TAG, "I2C Slave init at address: 0x" << _HEX(_addr));
//  return i2c_driver_install(i2c_slave_port, I2C_MODE_SLAVE, I2C_SLAVE_RX_BUF_LEN, I2C_SLAVE_TX_BUF_LEN, 0);
//}

//  void I2CSlave::onWifiConnected() { }
//  void I2CSlave::onWifiDisconnected() { }
//  void I2CSlave::onMqttConnected() { }
//  void I2CSlave::onMqttDisconnected() { }
//  bool I2CSlave::handleMqttMessage(const char *topic, int id, const char *cmd, const JsonDocument& json) {
//    return false; // false means not handled
//  }
//bool I2CSlave::handleCommand(const std::string& cmd) {
//  if (cmd == "I2 Task") {
//    PUTLN("");
//
//  } else {
//    return false; // false means not handled
//  }
//
//  return true;
//}
#if ENABLE_I2C_OLED_DISPLAY_PLUGIN
//  void I2CSlave::addFramesAndOverlays() { }
#endif

#endif // CONFIG_ENABLE_I2C_SLAVE
