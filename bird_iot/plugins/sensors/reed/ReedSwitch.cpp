#include "ReedSwitch.h"

bool ReedSwitch::setup() {
  pinMode(_pin, _pinMode);

  if (_pinMode == INPUT_PULLUP) {
    gpio_pullup_en(_pin);
    gpio_pulldown_dis(_pin);
  } else if (_pinMode == INPUT_PULLDOWN) {
    gpio_pullup_dis(_pin);
    gpio_pulldown_en(_pin);
  }

  return true;
}

uint8_t ReedSwitch::read() {
  uint8_t val = digitalRead(_pin);
  if (!_normallyOpen) {
    val = !val;
  }
  return val;
}
