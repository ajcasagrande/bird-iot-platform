#pragma once

#include "colors.h"

struct OnOff {
  bool on;
  uint ms;
};

struct StatusLedMode {
  bool on;
  bool blink;
  uint8_t length;
  uint32_t *timings;

  OnOff next(uint8_t& index) {
    if (!blink) {
      return {on, 1000};
    }

    OnOff rVal = {index % 2 == 0, timings[index]};
    index++;
    if (index >= length) {
      index = 0;
    }
    return rVal;
  }
};

#define NUMARGS(...)  (sizeof((uint32_t[]){__VA_ARGS__})/sizeof(uint32_t))

#define timings(...)   NUMARGS(__VA_ARGS__),(uint32_t[]){__VA_ARGS__}

static const StatusLedMode LED_OFF = {false, false, 0, nullptr};
static const StatusLedMode LED_ALWAYS_ON = {true, false, 0, nullptr};
static const StatusLedMode LED_NORMAL = {true, true, timings(1000, 100, 100, 100, 5000, 100)};
static const StatusLedMode LED_SLOW_BLINK = LED_NORMAL;
static const StatusLedMode LED_FAST_BLINK = {true, true, timings(100, 100, 50, 50)};
static const StatusLedMode LED_MEDIUM_BLINK = LED_NORMAL;

#undef on
#undef off
#undef timings
