#include "GaragePlugin.h"
#if CONFIG_ENABLE_GARAGE_PLUGIN

static const char* const TAG = "Garage";

#if CONFIG_ENABLE_TFT_DISPLAY
#include "TFTDisplayPlugin.h"
#include "TftHelpers.h"
#endif

bool GaragePlugin::setup() {
  REQUIRE_VALID_OUTPUT_PIN(pin);

  pinMode(pin, OUTPUT);
  digitalWrite(pin, offState);
#if CONFIG_ENABLE_TFT_DISPLAY
  TFTDisplayManager.registerOverlay(this);
#endif

  return true;
}

void GaragePlugin::toggleGarage() {
  lastToggleMs = millis();
#if CONFIG_ENABLE_TFT_DISPLAY
  this->setDirty(true);
#endif

  xSemaphoreTakeRecursive(pinMutex, portMAX_DELAY);

  LOGI(TAG, ">> toggleGarage()");
//  App.setStatusColor(LED_PINK);

  LOGI(TAG, "\tdigitalWrite(" << pin << ", onState)");
  digitalWrite(pin, onState);

  LOGI(TAG, "\ttaskDELAY(" << CONFIG_GARAGE_RELAY_DELAY << ")");
  taskDELAY(CONFIG_GARAGE_RELAY_DELAY);

  LOGI(TAG, "\tdigitalWrite(" << pin << ", offState)");
  digitalWrite(pin, offState);

//  App.setStatusColor(LED_ONLINE);
  LOGI(TAG, " << toggleGarage()");
  xSemaphoreGiveRecursive(pinMutex);
}

void GaragePlugin::onMqttConnected() {
  Mqtt.subscribe(GARAGE_MQTT_TOPIC);
}

bool GaragePlugin::handleMqttMessage(const char *topic, const int id, const char *cmd, const JsonDocument& json) {
  if (strcmp(topic, GARAGE_MQTT_TOPIC) != 0) {
    return false;
  }

  if (strcmp(cmd, "open") == 0
      || strcmp(cmd, "close") == 0
      || strcmp(cmd, "toggle") == 0) {
    toggleGarage();
  } else if (strcmp(cmd, "double_toggle") == 0) {
    toggleGarage();
    taskDELAY(CONFIG_GARAGE_DOUBLE_TOGGLE_DELAY);
    toggleGarage();
  } else {
    LOGI(TAG, "unknown command");
    return false;
  }

  Mqtt.respondTrue(id);
  return true;
}

#if CONFIG_ENABLE_TFT_DISPLAY
void GaragePlugin::draw(TFT_eSPI *img, DisplayUI& ui) {
  img->setFreeFont(font);

  bool expired = millis() - lastToggleMs > 2500;
  const char* str = expired ? "      " : "Garage";

  int16_t textWidth = tftMeasureString(img, (char*)str, font);
  tftDrawString(img, (char*)str, nullptr, ui.maxX - textWidth, img->glyph_ab - img->glyph_bb, 0xB5B6, ui.bgColor, font, true);

  if (expired) {
    // once we have expired, draw last time and then reset lastToggleMs so it doesn't get drawn again
    lastToggleMs = 0;
  }
}

bool GaragePlugin::isDirty() {
  return lastToggleMs != 0;
}

#endif // CONFIG_ENABLE_TFT_DISPLAY

#endif // CONFIG_ENABLE_GARAGE_PLUGIN
