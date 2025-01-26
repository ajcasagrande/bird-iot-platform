#pragma once

#include <Arduino.h>

class ReedSwitch {
private:
  gpio_num_t _pin;
  bool _normallyOpen;
  uint8_t _pinMode;
public:
  explicit ReedSwitch(gpio_num_t pin, bool normallyOpen=true, uint8_t pinMode=INPUT_PULLUP)
                        : _pin(pin), _normallyOpen(normallyOpen), _pinMode(pinMode) { }

  bool setup();
  uint8_t read();
};
