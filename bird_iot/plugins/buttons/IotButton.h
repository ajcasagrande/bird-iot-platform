#pragma once

#include "sdkconfig.h"
#include "builtin.h"

#if CONFIG_ENABLE_BUTTON_PLUGIN

#include <EasyButton.h>

#include <utility>

class IotButton {
public:
  IotButton(const char* name, uint8_t pin, uint32_t eventBits,
      std::function<void()> callback = nullptr, std::function<void()> longCallback = nullptr)
            : name(name), pin(pin), eventBits(eventBits), easyButton(pin),
              callback(std::move(callback)), longCallback(std::move(longCallback)) {

  }

  const char* name;
  uint8_t pin;
  uint32_t eventBits;
  EasyButton easyButton;
  std::function<void()> callback;
  std::function<void()> longCallback;

  void setup();
  static void isr(void* button);
  bool read();

private:

};

#endif // CONFIG_ENABLE_BUTTON_PLUGIN
