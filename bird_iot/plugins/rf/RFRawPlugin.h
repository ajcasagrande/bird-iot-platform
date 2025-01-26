#pragma once
#include "sdkconfig.h"

#if CONFIG_ENABLE_RF_RAW_PLUGIN

#include "common.h"

class RFRawPlugin : public IotPlugin {
public:
  explicit RFRawPlugin(uint8_t _pin);

  bool setup() override;
  bool start() override;
  void execute();

  static void isr(void* raw);

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
  Task<RFRawPlugin> *task;
  uint8_t rxPin;
  unsigned int timings[CONFIG_RF_RAW_SAMPLE_SIZE];
  unsigned int pos = 0;
  unsigned long lastTime = 0;
};

#endif // CONFIG_ENABLE_RF_RAW_PLUGIN
