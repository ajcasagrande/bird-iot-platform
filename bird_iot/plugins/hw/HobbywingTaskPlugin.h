#pragma once
#include "sdkconfig.h"

#if CONFIG_ENABLE_HOBBYWING_TASK_PLUGIN

#include "common.h"

#define BUFFER_SIZE (32)
#define RESULT_SIZE (9)
#define MAX_DUPES (100)

class HobbywingTaskPlugin : public IotPlugin {
public:
  HobbywingTaskPlugin();

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
  Task<HobbywingTaskPlugin> *task;
  HardwareSerial *hwSerial;

  void handleBuffer();
  void printResult();

  uint8_t buffer[BUFFER_SIZE];
  uint8_t buffer1[BUFFER_SIZE];
  int bufferIndex = 0;
  bool bufferFlag = false;
  uint32_t prevMs = 0;
  uint32_t currMs = 0;
  uint32_t dupePrevMs = 0;
  uint32_t dupeCount = 0;

  uint8_t result[RESULT_SIZE];
};

extern HobbywingTaskPlugin HobbywingTask;

#endif // CONFIG_ENABLE_HOBBYWING_TASK_PLUGIN
