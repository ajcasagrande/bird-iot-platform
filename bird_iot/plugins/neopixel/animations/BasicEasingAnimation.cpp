#include "BasicEasingAnimation.h"
#include "sdkconfig.h"

#if CONFIG_ENABLE_NEOPIXEL_DRIVER

static HtmlColor colors[] = {
    0x7f0000,
    0x007f00,
    0x00007f,
    0x007f7f,
    0x7f7f00,
    0x7f007f
};
static int8_t colorCount = 6;

void BasicEasingAnimation::setupAnimationSet() {
  // setup some animations
  for (uint16_t pixel = 0; pixel < driver->count; pixel++) {
//    const uint8_t peak = 192;

    // pick a random duration of the animation for this pixel
    // since values are centiseconds, the range is 1 - 4 seconds
    uint16_t time = random(25, 75);

    // each animation starts with the color that was present
    RgbColor originalColor = driver->pixels->GetPixelColor(pixel);
    // and ends with a random color
    // RgbColor targetColor = RgbColor(random(peak), random(peak), random(peak));
   HtmlColor targetColor = colors[random(colorCount)];

    // with the random ease function
    AnimEaseFunction easing;

    switch (random(3)) {
      case 0:
        easing = NeoEase::CubicIn;
        break;
      case 1:
        easing = NeoEase::CubicOut;
        break;
      case 2:
        easing = NeoEase::QuadraticInOut;
        break;
    }

    // we must supply a function that will define the animation, in this example
    // we are using "lambda expression" to define the function inline, which gives
    // us an easy way to "capture" the originalColor and targetColor for the call back.
    //
    // this function will get called back when ever the animation needs to change
    // the state of the pixel, it will provide a animation progress value
    // from 0.0 (start of animation) to 1.0 (end of animation)
    //
    // we use this progress value to define how we want to animate in this case
    // we call RgbColor::LinearBlend which will return a color blended between
    // the values given, by the amount passed, hich is also a float value from 0.0-1.0.
    // then we set the color.
    AnimUpdateCallback animUpdate = [=](const AnimationParam& param) {
      // progress will start at 0.0 and end at 1.0
      // we convert to the curve we want
      float progress = easing(param.progress);

      // use the curve value to apply to the animation
      RgbColor updatedColor = RgbColor::LinearBlend(originalColor, targetColor, progress);
      driver->pixels->SetPixelColor(pixel, updatedColor);
    };

    // now use the animation properties we just calculated and start the animation
    // which will continue to run and call the update function until it completes
    animations->StartAnimation(pixel, time, animUpdate);
  }
}

void BasicEasingAnimation::setup() {
  setupAnimationSet();
  driver->pixels->Show();
}

void BasicEasingAnimation::loop() {
  if (animations->IsAnimating()) {
    // the normal loop just needs these two to run the active animations
    animations->UpdateAnimations();
    driver->pixels->Show();
  } else {
    setupAnimationSet();
  }
}

#endif  // CONFIG_ENABLE_NEOPIXEL_DRIVER
