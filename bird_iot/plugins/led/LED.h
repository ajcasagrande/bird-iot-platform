#pragma once

#include "include/common.h"

class LED {
private:
  uint8_t _pin;
  bool invert;
  bool enabled;
  uint8_t onState;
  uint8_t offState;

  uint8_t modeIndex = 0;

public:
  explicit LED(bool enabled = true, pin_t p = 0, StatusLedMode defaultMode = LED_NORMAL, bool invert = true);

  Ticker ticker;
  StatusLedMode defaultMode;
  StatusLedMode currentMode;

  void write(uint8_t state);
  void mode(StatusLedMode mode);
  void reset();
  void next();
  bool setup();
};

extern LED StatusLed;
extern LED NetworkLed;
