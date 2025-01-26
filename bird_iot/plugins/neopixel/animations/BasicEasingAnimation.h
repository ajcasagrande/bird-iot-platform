#pragma once

#include "sdkconfig.h"

#if CONFIG_ENABLE_NEOPIXEL_DRIVER

#include "AbstractAnimation.h"
#include "NeoPixelDriver.h"

class BasicEasingAnimation : public AbstractAnimation {
public:
  explicit BasicEasingAnimation(NeoPixelDriver *driver)
    : AbstractAnimation(driver, new NeoPixelAnimator(driver->count, NEO_CENTISECONDS)) { }

  void setup() override;
  void loop() override;

  void setupAnimationSet();
};

#endif   // CONFIG_ENABLE_NEOPIXEL_DRIVER
