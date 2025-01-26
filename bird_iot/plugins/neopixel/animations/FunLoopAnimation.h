#pragma once

#include "sdkconfig.h"

#if CONFIG_ENABLE_NEOPIXEL_DRIVER

#include "AbstractAnimation.h"
#include "NeoPixelDriver.h"

// what is stored for state is specific to the need, in this case, the colors and
// the pixel to animate;
// basically what ever you need inside the animation update function
struct FunLoopAnimationState
{
  RgbColor StartingColor;
  RgbColor EndingColor;
  uint16_t IndexPixel; // which pixel this animation is effecting
};

class FunLoopAnimation : public AbstractAnimation {
public:
  uint16_t pixelFadeDuration = 300; // third of a second
// one second divide by the number of pixels = loop once a second
  uint16_t nextPixelMoveDuration; // how fast we move through the pixels

  uint16_t animCount; // we only need enough animations for the tail and one extra
  FunLoopAnimationState *animationState;

  NeoGamma<NeoGammaTableMethod> colorGamma; // for any fade animations, best to correct gamma

  explicit FunLoopAnimation(NeoPixelDriver *driver)
      : AbstractAnimation(driver, new NeoPixelAnimator(driver->count / 5 * 2 + 1)),
        nextPixelMoveDuration(1000 / driver->count),
        animCount(driver->count / 5 * 2 + 1) {
    animationState = (FunLoopAnimationState *)malloc(animCount * sizeof(FunLoopAnimationState));
  }

  ~FunLoopAnimation() {
    free(animationState);
  }

  void setup() override;
  void loop() override;

  void FadeOutAnimUpdate(const AnimationParam &param);

  void LoopAnimUpdate(const AnimationParam &param);
};


#endif   // CONFIG_ENABLE_NEOPIXEL_DRIVER
