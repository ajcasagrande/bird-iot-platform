#include "ButtonPlugin.h"
#if CONFIG_ENABLE_BUTTON_PLUGIN

#include "TFTDisplayPlugin.h"

#define BUTTON_1_EVENT_BITS (1 << 0)
#define BUTTON_2_EVENT_BITS (1 << 1)
#define BUTTON_A_EVENT_BITS (1 << 2)
#define BUTTON_B_EVENT_BITS (1 << 3)

//static const char* TAG = "Button";

ButtonPluginClass ButtonPlugin;

ButtonPluginClass::ButtonPluginClass() : IotPlugin("Button Plugin") { }


static void _execute() {
  uint32_t ulInterruptStatus;
  xTaskNotifyWait(0x00,               /* Don't clear any bits on entry. */
                  ULONG_MAX,          /* Clear all bits on exit. */
                  &ulInterruptStatus, /* Receives the notification value. */
                  portMAX_DELAY);    /* Block indefinitely. */

  for (auto & btn : ButtonPlugin.buttons) {
    if ((ulInterruptStatus & btn->eventBits) != 0x00) {
      // Note: Do not call break, as more than one bit can be set
      btn->read();
    }
  }
}

bool ButtonPluginClass::setup() {
#ifdef BUTTON_1
  buttons.push_back(new IotButton("1", BUTTON_1, BUTTON_1_EVENT_BITS,
#if CONFIG_ENABLE_TFT_DISPLAY
      std::bind(&TFTDisplayPlugin::increaseBacklight, &TFTDisplay, 10, true)
#endif
  ));
#endif // BUTTON_1

#ifdef BUTTON_2
  buttons.push_back(new IotButton("2", BUTTON_2, BUTTON_2_EVENT_BITS,
#if CONFIG_ENABLE_TFT_DISPLAY
      std::bind(&TFTDisplayPlugin::toggleRotation, &TFTDisplay)
#endif
    ));
#endif // BUTTON_2

#ifdef BUTTON_A
  buttons.push_back(new IotButton("A", BUTTON_A, BUTTON_A_EVENT_BITS,
#if CONFIG_ENABLE_TFT_DISPLAY
      std::bind(&TFTDisplayPlugin::increaseBacklight, &TFTDisplay, 10, true)
#endif
  ));
#endif // BUTTON_A

#ifdef BUTTON_B
  buttons.push_back(new IotButton("B", BUTTON_B, BUTTON_B_EVENT_BITS,
#if CONFIG_ENABLE_TFT_DISPLAY
      std::bind(&TFTDisplayPlugin::toggleRotation, &TFTDisplay)
#endif
  ));
#endif // BUTTON_B

  task = new VoidTask("Button Task", _execute);
  return task->configure(0, _2k, ONE_BELOW_MAX, CORE_0, false, true, 0);
}

bool ButtonPluginClass::start() {
  bool res = task->start();
  // note: waiting to call setup on the buttons because we do not want to trigger events before the task has started
  for (auto & btn : buttons) {
    btn->setup();
  }
  return res;
}

//  void ButtonPluginClass::onWifiConnected() { }
//  void ButtonPluginClass::onWifiDisconnected() { }
//  void ButtonPluginClass::onMqttConnected() { }
//  void ButtonPluginClass::onMqttDisconnected() { }
//  bool ButtonPluginClass::handleMqttMessage(const char *topic, int id, const char *cmd, const JsonDocument& json) {
//   return false; // false means not handled 
// }
//  bool ButtonPluginClass::handleCommand(const std::string& cmd) {
//   return false; // false means not handled 
// }
#if ENABLE_I2C_OLED_DISPLAY_PLUGIN
//  void ButtonPluginClass::addFramesAndOverlays() { }
#endif

#endif // CONFIG_ENABLE_BUTTON_PLUGIN
