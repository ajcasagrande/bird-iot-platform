#pragma once
#include "sdkconfig.h"

#if CONFIG_ENABLE_SOIL_SENSOR

#include "common.h"

const uint16_t minRawMoistureValue = 250;

class SoilSensor : public BaseSensor {
public:
  gpio_num_t pin;

  FloatStats stats;

  explicit SoilSensor(gpio_num_t pin);

  bool setup() override;
  void poll() override;
  void publishData() override;

  void markInvalidData();

//  void onWifiConnected() override;
//  void onWifiDisconnected() override;
//  void onMqttConnected() override;
//  void onMqttDisconnected() override;
//  bool handleMqttMessage(const char *topic, int id, const char *cmd, const JsonDocument& json) override;
//  bool handleCommand(const std::string& cmd) override;
#if ENABLE_I2C_OLED_DISPLAY_PLUGIN
//  void addFramesAndOverlays() override;
#endif
};

#endif // CONFIG_ENABLE_SOIL_SENSOR
