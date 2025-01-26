#pragma once

#include "sdkconfig.h"

#if CONFIG_ENABLE_NEOPIXEL_DRIVER

class NeoPixelDriver;

#include <NeoPixelAnimator.h>

class AbstractAnimation {
public:
  explicit AbstractAnimation(NeoPixelDriver *driver, NeoPixelAnimator *animations)
      : driver(driver), animations(animations) { }

  virtual ~AbstractAnimation() { delete animations; }

  virtual void setup() { }
  virtual void loop() { }
  virtual void pause() { animations->Pause(); }

protected:
  NeoPixelDriver *driver;
  NeoPixelAnimator *animations;

};

#endif  // CONFIG_ENABLE_NEOPIXEL_DRIVER
