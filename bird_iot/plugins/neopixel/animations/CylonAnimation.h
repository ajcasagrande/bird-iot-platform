#pragma once

#include "sdkconfig.h"

#if CONFIG_ENABLE_NEOPIXEL_DRIVER

#include "NeoPixelDriver.h"
#include "AbstractAnimation.h"

class CylonAnimation : public AbstractAnimation {
public:
  explicit CylonAnimation(NeoPixelDriver *driver)
      : AbstractAnimation(driver, new NeoPixelAnimator(2)) { }

  void setup() override;
  void loop() override;

  RgbColor cylonEyeColor = HtmlColor(0x7f0000);
  uint16_t lastPixel = 0; // track the eye position
  int8_t moveDir = 1; // track the direction of movement
  AnimEaseFunction moveEase = NeoEase::QuarticInOut;

  void FadeAnimUpdate(const AnimationParam &param);
  void MoveAnimUpdate(const AnimationParam &param);
  void FadeAll(uint8_t darkenBy);
};


#endif  // CONFIG_ENABLE_NEOPIXEL_DRIVER

