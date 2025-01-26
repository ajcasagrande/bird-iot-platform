#pragma once
#include "sdkconfig.h"

#if CONFIG_ENABLE_RF_SNIFFER_PLUGIN

#include "include/common.h"
#include "tasks/TaskClass.h"

#include <RCSwitch.h>

class RFSnifferPlugin : public IotPlugin {
private:
  RCSwitch rf;
  uint freq;
  uint8_t rxPin;
  Task<RFSnifferPlugin> *task;
  unsigned int rawTimings[CONFIG_RF_SNIFFER_RAW_SAMPLE_SIZE];
  unsigned volatile int rawPos = 0;
  unsigned volatile long rawLastTime = 0;

public:
  RFSnifferPlugin(uint _freq, uint8_t _pin);

  void execute();
  bool setup() override;
  bool start() override;

  static void isr(void* sniffer);

  bool handleCommand(const std::string& cmd) override;

  void doRawRFScan();
};

#endif // CONFIG_ENABLE_RF_SNIFFER_PLUGIN
