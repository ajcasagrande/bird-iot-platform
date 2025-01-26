#pragma once

#include "sdkconfig.h"

#if CONFIG_ENABLE_IR_PLUGIN

#include "IotPlugin.h"

class IRPlugin : public IotPlugin {
private:
  int pin;

  void send_lg_ac(const char*, int);
  void send_nec(const char*, int);
  void sendIRCode(const char*, int, const char*);
  void space(long);
  void mark(long);
  void send_generic(const char*, int,
                    int, int,
                    int, int,
                    int, int,
                    int, int);
public:
  // IotPlugin implementation
  explicit IRPlugin(int);
  bool setup() override;
//  bool start() override;
  void onMqttConnected() override;
  bool handleMqttMessage(const char *topic, int id, const char *cmd, const JsonDocument& json) override;
};

#endif // CONFIG_ENABLE_IR_PLUGIN
