#include "IotButton.h"

#if CONFIG_ENABLE_BUTTON_PLUGIN

#include "ButtonPlugin.h"

static const char* TAG = "Button";

void IotButton::setup() {
  easyButton.begin();

  if (callback != nullptr) {
    easyButton.onPressed([this]() {
      LOGD(TAG, "Button " << name << " was pressed!");
      callback();
    });
  }

  if (longCallback != nullptr) {
    easyButton.onPressedFor(CONFIG_LONG_PRESS_DELAY, [this]() {
      LOGD(TAG, "Button " << name << " was long-pressed!");
      longCallback();
    });
  }

  pinMode(pin, INPUT_PULLUP);
  attachInterrupt(pin, std::bind(&IotButton::isr,this), CHANGE);
}

void IRAM_ATTR IotButton::isr(void* button) {
  auto self = static_cast<IotButton*>(button);
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;

  xTaskNotifyFromISR(ButtonPlugin.task->getHandle(),
                     self->eventBits,
                     eSetBits,
                     &xHigherPriorityTaskWoken);

  if (xHigherPriorityTaskWoken == pdTRUE) {
    portYIELD_FROM_ISR();
  }
}

bool IotButton::read() {
  easyButton.update();
  return easyButton.read(EASYBUTTON_INTERRUPT);
}

#endif // CONFIG_ENABLE_BUTTON_PLUGIN
