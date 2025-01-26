#pragma once

#include "RunMode.h"
#include <Ticker.h>

class SafeModeClass : public RunMode {
private:
  bool enableMqtt = false;
  Ticker ticker;

public:
  SafeModeClass* withMqtt() { enableMqtt = true; return this; }
  bool isMqttEnabled() { return enableMqtt; }
  bool activate() override;
};

extern SafeModeClass SafeMode;
