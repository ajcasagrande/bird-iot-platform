#include "i2cDriver.h"

#if CONFIG_ENABLE_I2C_DRIVER

#define LOG_ERR_MISSING_LIB(name, flag)  LOGE(TAG, "Found i2c " name " at address 0x" << _HEX(address) << ", however support has not been enabled. Please enable `" #flag "` and recompile."); 

I2CDriver i2cDriver(SDA, SCL);

#include <Wire.h>
#include <vector>
#include <driver/i2c.h>

#include "sensor_addresses.h"
#include "i2c_sensors_inc.h"

#define addressInRange(_min, _max) (address >= _min && address <= _max)
#define addressIsEither(a, b) (address == a || address == b)

#define I2C_MASTER_TX_BUF_DISABLE 0 /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE 0 /*!< I2C master doesn't need buffer */
#define WRITE_BIT I2C_MASTER_WRITE  /*!< I2C master write */
#define READ_BIT I2C_MASTER_READ    /*!< I2C master read */
#define ACK_CHECK_EN 0x1            /*!< I2C master will check ack from slave*/
#define ACK_CHECK_DIS 0x0           /*!< I2C master will not check ack from slave */
#define ACK_VAL 0x0                 /*!< I2C ack value */
#define NACK_VAL 0x1                /*!< I2C nack value */

static uint32_t i2c_frequency = 100000;
static i2c_port_t i2c_port = I2C_NUM_0;

static const char* TAG = "i2c";

esp_err_t I2CDriver::i2c_master_driver_initialize() {
  auto *conf = new(i2c_config_t);
  conf->mode = I2C_MODE_MASTER;
  conf->sda_io_num = gpio_num_t(_sda);
  conf->sda_pullup_en = GPIO_PULLUP_ENABLE;
  conf->scl_io_num = gpio_num_t(_scl);
  conf->scl_pullup_en = GPIO_PULLUP_ENABLE;
  conf->master = {i2c_frequency};
  return i2c_param_config(i2c_port, conf);
}

bool I2CDriver::setup() {
  if (!initialized) {
    initialized = true;
    autoRegister();

    LOGI(TAG, "wire.begin(" << _sda << "," << _scl << ")");
    lock();
    Wire.begin(_sda, _scl);
    unlock();
  }
  return true;
}

void I2CDriver::scanIDF(std::vector<uint8_t> &found) {
  lock();

  i2c_master_driver_initialize();
  i2c_driver_install(i2c_port, I2C_MODE_MASTER, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);

  for (uint8_t address = 0; address < 128; address++) {
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (address << 1) | WRITE_BIT, ACK_CHECK_EN);
    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(i2c_port, cmd, 50 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
    if (ret == ESP_OK) {
      found.push_back(address);
    }
  }

  i2c_driver_delete(i2c_port);
  unlock();
}

void I2CDriver::scan(std::vector<uint8_t> &found) {
  LOGI(TAG, "Scanning for i2c devices...");

  lock();
  for (uint8_t address = 1; address < 127; address++) {
    // The i2c_scanner uses the return value of the Write.endTransmission to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    uint8_t error = Wire.endTransmission();

    if (error == 0) {
      LOGI(TAG, "Found i2c device at address 0x" << _HEX(address) << " !");
      found.push_back(address);
    } else if (error == 4) {
      LOGE(TAG, "Unknown error at address 0x" << _HEX(address));
    }
  }
  unlock();

  if (found.empty()) {
    LOGI(TAG, "No i2c devices were found");
  } else {
    LOGI(TAG, "Scan found " << found.size() << " i2c device(s)");
  }
}

void I2CDriver::scanAndPublish() {
  LOGD(TAG, "Scan and publish i2c called");
  auto found = new std::vector<uint8_t>();
  scan(*found);

  const size_t capacity = JSON_ARRAY_SIZE(found->size() + 1) + JSON_OBJECT_SIZE(1);
  DynamicJsonDocument doc(capacity);
  JsonArray results_found = doc.createNestedArray("found");
  char fmt[6];
  for (uint8_t addr : *found) {
    simpleHexFormat(reinterpret_cast<char *>(&fmt), addr, 2);
    results_found.add(fmt);
  }
  sentScan = sentScan || Mqtt.publish(Mqtt.topics.i2c_scan, doc);

  found->clear();
  delete(found);
}

void I2CDriver::registerI2CPlugin(IotPlugin *plugin, int address) {
  LOGI(TAG, "Registering i2c device " << plugin->name << " at address 0x" << _HEX(address));
  App.registerPlugin(plugin);
}

void I2CDriver::autoRegister() {
  LOGI(TAG, "Auto registering i2c devices...");

  std::vector<uint8_t> found;
  scanIDF(found);
  for (uint8_t address : found) {
    LOGD(TAG, "address: 0x" << _HEX(address));

  if (address == QMC5883L_COMPASS_ADDRESS) {
#if CONFIG_ENABLE_QMC5883L_COMPASS_SENSOR
    registerI2CPlugin(new QMC5883LCompass(), address);
#else
    LOG_ERR_MISSING_LIB("QMC5883L Compass", CONFIG_ENABLE_QMC5883L_COMPASS_SENSOR);
#endif

  } else if (addressInRange(MCP9808_BASE_ADDRESS, MCP9808_MAX_ADDRESS)) {
#if CONFIG_ENABLE_MCP9808_SENSOR
      registerI2CPlugin(new MCP9808Sensor(address), address);
#else
      LOG_ERR_MISSING_LIB("MCP9808 Sensor", CONFIG_ENABLE_MCP9808_SENSOR);
#endif

    } else if (address == NFC_PN532_ADDRESS) {
#if CONFIG_ENABLE_NFC_DRIVER_532
      registerI2CPlugin(new NFCDriver532(), address);
#else
      LOG_ERR_MISSING_LIB("NFC PN532", CONFIG_ENABLE_NFC_DRIVER_532);
#endif

    } else if (addressIsEither(LCD_CHARACTER_DISPLAY_ADDRESS_A, LCD_CHARACTER_DISPLAY_ADDRESS_B)) {
#if CONFIG_ENABLE_I2C_LCD_CHARACTER_DISPLAY
      App.registerLcd(new LcdDriver(address, 16, 2));
#else
      LOG_ERR_MISSING_LIB("LCD Character Display", CONFIG_ENABLE_I2C_LCD_CHARACTER_DISPLAY);
#endif

    } else if (addressIsEither(OLED_DISPLAY_ADDRESS_A, OLED_DISPLAY_ADDRESS_B)) {
#if CONFIG_ENABLE_I2C_OLED_DISPLAY_PLUGIN
      App.registerOledDisplay(new OledDisplayPlugin(address));
#else
      LOG_ERR_MISSING_LIB("OLED display", CONFIG_ENABLE_I2C_OLED_DISPLAY_PLUGIN);
#endif

    } else if (address == HDC1008_ADDRESS) {
#if CONFIG_ENABLE_HDC1008_SENSOR
      auto *hdc = new HDC1008Sensor(address);
      if (hdc->checkInit()) {
        registerI2CPlugin(hdc, address);

      } else {
#endif
#if CONFIG_ENABLE_HTU21D_SENSOR
        registerI2CPlugin(new HTU21DSensor(), address);
#else
        LOG_ERR_MISSING_LIB("HTU21D Sensor", CONFIG_ENABLE_HTU21D_SENSOR);
#endif
#if CONFIG_ENABLE_HDC1008_SENSOR
      }
#endif

    } else if (addressInRange(LM75A_BASE_ADDRESS, LM75A_MAX_ADDRESS)) {
#if CONFIG_ENABLE_LM75A_SENSOR
      registerI2CPlugin(new LM75ASensor(address), address);
#else
      LOG_ERR_MISSING_LIB("LM75A Sensor", CONFIG_ENABLE_LM75A_SENSOR);
#endif

    } else if (addressInRange(BMP280_MIN_ADDRESS, BMP280_MAX_ADDRESS)) {
#if CONFIG_ENABLE_BMP280_SENSOR
      registerI2CPlugin(new BMP280Sensor(address), address);
#else
      LOG_ERR_MISSING_LIB("BMP280 Sensor", CONFIG_ENABLE_BMP280_SENSOR);
#endif

    } else if (address == AXP192_ADDRESS) {
#if CONFIG_ENABLE_AXP192_SENSOR
      registerI2CPlugin(&AXP192Sensor, address);
#else
      LOG_ERR_MISSING_LIB("AXP192 Sensor", CONFIG_ENABLE_AXP192_SENSOR);
#endif

    } else if (address == M5_RTC_ADDRESS) {
      // todo
      LOGW(TAG, "Detected unsupported i2c device at address 0x" << _HEX(address) << " (M5 Stick-C RTC)");

    } else if (address == MPU6886_ADDRESS) {
      // todo
      LOGW(TAG, "Detected unsupported i2c device at address 0x" << _HEX(address) << " (MPU6886 IMU)");

    } else {
      LOGW(TAG, "Detected unsupported i2c device at address 0x" << _HEX(address));
    }
  }

  LOGI(TAG, "Done registering i2c devices");
}

void I2CDriver::onMqttConnected() {
  Mqtt.subscribe(I2C_MQTT_TOPIC);

  if (!sentScan) {
    scanAndPublish();
  }
}

bool I2CDriver::handleMqttMessage(const char *topic, const int id, const char *cmd, const JsonDocument& json) {
  if (strcmp(topic, I2C_MQTT_TOPIC) != 0) {
    return false;
  }

  if (strcmp(cmd, "scan") == 0) {
    scanAndPublish();
  } else {
    LOGI(TAG, "unknown command");
    return false;
  }

  Mqtt.respondTrue(id);
  return true;
}

bool I2CDriver::handleCommand(const std::string& cmd) {
  if (cmd == "i2c scan") {
    scanAndPublish();
    return true;
  }

  return false;
}

#endif // CONFIG_ENABLE_I2C_DRIVER
