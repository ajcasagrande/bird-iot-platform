#include "LED.h"
#include "sdkconfig.h"

static const char* TAG = "Status LED";

LED StatusLed(CONFIG_LED_BUILTIN_PIN >= 0, CONFIG_LED_BUILTIN_PIN, LED_NORMAL,
#if CONFIG_INVERT_STATUS_LED
  true
#else
  false
#endif
);

LED NetworkLed(CONFIG_NETWORK_LED_PIN >= 0, CONFIG_NETWORK_LED_PIN, LED_OFF,
#if CONFIG_INVERT_NETWORK_LED
  true
#else
  false
#endif
);

LED::LED(bool enabled, pin_t p, StatusLedMode defaultMode, bool invert) {
  this->_pin = p;
  this->defaultMode = defaultMode;
  this->currentMode = defaultMode;
  this->invert = invert;
  this->enabled = enabled;

  this->onState = HIGH;
  if (invert) {
    this->onState = LOW;
  }
  this->offState = !this->onState;
}

void onTick() {
  StatusLed.next();
}

bool LED::setup() {
  if (enabled) {
    REQUIRE_VALID_OUTPUT_PIN(_pin);
    LOGD(TAG, "OUTPUT to " << onState);
    pinMode(_pin, OUTPUT);
    mode(defaultMode);
  }

  return true;
}

void LED::reset() {
  mode(defaultMode);
}

void LED::mode(StatusLedMode mode) {
  if (!enabled) {
    return;
  }

  currentMode = mode;
  modeIndex = 0;

  if (mode.on && mode.blink) {
    next();
  } else {
    ticker.detach();
    write(mode.on ? onState : offState);
  }
}

void LED::next() {
  OnOff o = currentMode.next(modeIndex);
  write(o.on ? onState : offState);
  ticker.once_ms(o.ms, onTick);
}

void LED::write(uint8_t state) {
  digitalWrite(_pin, state);
}
