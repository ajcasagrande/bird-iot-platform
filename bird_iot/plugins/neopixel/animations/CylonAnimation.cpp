#include "CylonAnimation.h"

#if CONFIG_ENABLE_NEOPIXEL_DRIVER

// NeoPixelCylon
// This example will move a Cylon Red Eye back and forth across the
// the full collection of pixels on the driver->pixels->
//
// This will demonstrate the use of the NeoEase animation ease methods; that provide
// simulated acceleration to the animations->
//
//

#include <NeoPixelBus.h>
#include <NeoPixelAnimator.h>

void CylonAnimation::FadeAll(uint8_t darkenBy) {
  RgbColor color;
  for (uint16_t indexPixel = 0; indexPixel < driver->count; indexPixel++) {
    color = driver->pixels->GetPixelColor(indexPixel);
    color.Darken(darkenBy);
    driver->pixels->SetPixelColor(indexPixel, color);
  }
}

void CylonAnimation::FadeAnimUpdate(const AnimationParam& param) {
  if (param.state == AnimationState_Completed) {
    FadeAll(10);
    animations->RestartAnimation(param.index);
  }
}

void CylonAnimation::MoveAnimUpdate(const AnimationParam& param) {
  // apply the movement animation curve
  float progress = moveEase(param.progress);

  // use the curved progress to calculate the pixel to effect
  uint16_t nextPixel;
  if (moveDir > 0) {
    nextPixel = progress * driver->count;
  } else {
    nextPixel = (1.0f - progress) * driver->count;
  }

  // if progress moves fast enough, we may move more than
  // one pixel, so we update all between the calculated and
  // the last
  if (lastPixel != nextPixel) {
    for (uint16_t i = lastPixel + moveDir; i != nextPixel; i += moveDir) {
      driver->pixels->SetPixelColor(i, cylonEyeColor);
    }
  }
  driver->pixels->SetPixelColor(nextPixel, cylonEyeColor);

  lastPixel = nextPixel;

  if (param.state == AnimationState_Completed) {
    // reverse direction of movement
    moveDir *= -1;

    // done, time to restart this position tracking animation/timer
    animations->RestartAnimation(param.index);
  }
}

void CylonAnimation::setup() {
  // fade all pixels providing a tail that is longer the faster
  // the pixel moves.
  animations->StartAnimation(0, 5,
      [=](const AnimationParam& param) { FadeAnimUpdate(param); });

  // take several seconds to move eye from one side to the other
  animations->StartAnimation(1, 2000,
      [=](const AnimationParam& param) { MoveAnimUpdate(param); });

  driver->pixels->Show();
}

void CylonAnimation::loop() {
  animations->UpdateAnimations();
  driver->pixels->Show();
}


#endif  // CONFIG_ENABLE_NEOPIXEL_DRIVER
