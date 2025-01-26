#pragma once
#include "sdkconfig.h"

#if CONFIG_ENABLE_NEOPIXEL_DRIVER

#include "include/builtin.h"
#include "colors.h"
#include "IotPlugin.h"
#include "tasks/TaskClass.h"
#include "animations/AbstractAnimation.h"

#include <NeoPixelBus.h>
#include <NeoPixelAnimator.h>

typedef enum {
  READY,
  PAUSED,
  ANIMATING,
  STEADY
} NeoPixelMode;

class NeoPixelDriver : public IotPlugin {
public:
  uint16_t count;
  NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> *pixels;
  Task<NeoPixelDriver> *task;
  NeoPixelMode mode = READY;
  AbstractAnimation *animationMode = nullptr;

public:
  NeoPixelDriver(uint8_t pin, uint16_t count);

  bool setup() override;
  bool start() override;
  void onMqttConnected() override;
  bool handleMqttMessage(const char *topic, int id, const char *cmd, const JsonDocument& json) override;
  bool handleCommand(const std::string& cmd) override;

  void execute();
  void set(uint8_t index, RGB color);
  void setAll(RGB color);
  void pause();
  void resume();
};

#endif  // CONFIG_ENABLE_NEOPIXEL_DRIVER
