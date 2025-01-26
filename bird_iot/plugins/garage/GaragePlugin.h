#pragma once
#include "sdkconfig.h"

#if CONFIG_ENABLE_GARAGE_PLUGIN

#include "include/common.h"
#include "DisplayManager.h"

#if CONFIG_ENABLE_TFT_DISPLAY
#include "TFTDisplayPlugin.h"
#include "fonts/roboto.h"
#endif // CONFIG_ENABLE_TFT_DISPLAY

class GaragePlugin : public IotPlugin
#if CONFIG_ENABLE_TFT_DISPLAY
    , public Drawable
#endif
        {
private:
  QueueHandle_t pinMutex = xSemaphoreCreateMutex();
  gpio_num_t pin;
  uint8_t onState = LOW;
  uint8_t offState = !onState;
  uint64_t lastToggleMs;
  void toggleGarage();

public:
  explicit GaragePlugin(gpio_num_t pin) : IotPlugin("Garage Plugin"), pin(pin) { }
  bool setup() override;
//  bool start() override;
  void onMqttConnected() override;
  bool handleMqttMessage(const char *topic, int id, const char *cmd, const JsonDocument& json) override;

#if CONFIG_ENABLE_TFT_DISPLAY
  void draw(TFT_eSPI *img, DisplayUI& ui) override;
  bool isDirty() override;
  const GFXfont *font = &Roboto_Bold_18;
#endif

};

#endif // CONFIG_ENABLE_GARAGE_PLUGIN
