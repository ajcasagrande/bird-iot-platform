#include "TempSensor.h"

#include "TFTDisplayPlugin.h"
#if CONFIG_ENABLE_I2C_OLED_DISPLAY_PLUGIN
#include "oled_fonts.h"
#endif
#if CONFIG_ENABLE_TFT_DISPLAY
#include "TftHelpers.h"
#endif

bool TempSensor::setup() {
#if CONFIG_ENABLE_TFT_DISPLAY
  TFTDisplayManager.registerFrame(&temperatureFrame);
  if (hasHumiditySensor()) {
    TFTDisplayManager.registerOverlay(&humidityOverlay);
  }
#endif

  return pollTask->configure(_readInterval, _1p5, MEDIUM_PRIORITY) &&
         publishTask->configure(_publishInterval, _1p5, MEDIUM_PRIORITY);
}

bool TempSensor::validateHumidity(float h) {
  return h > 0.0 && h < 100.0;
}

bool TempSensor::validateTemp(float f) {
  return f > minValidTemp && f < maxValidTemp;
}

void TempSensor::addValues(float f, float h) {
  if (!validateHumidity(h) || !validateTemp(f)) {
    markInvalidData();
    return;
  }

  tempStats.addValue(f);
  humidityStats.addValue(h);
  if (tempStats.changed || humidityStats.changed) {
    LOGD(sensorName, "temp: " << f << " °" << unit << ", humidity: " << h << " %");
  }

#if CONFIG_ENABLE_TFT_DISPLAY
  if (tempStats.changed) {
    temperatureFrame.setDirty(true);
  }
  if (humidityStats.changed) {
    humidityOverlay.setDirty(true);
  }
#endif  
}

void TempSensor::addTempValue(float f) {
  if (!validateTemp(f)) {
    markInvalidData();
    return;
  }

#if CONFIG_ENABLE_I2C_LCD_CHARACTER_DISPLAY
  // TODO:
//  char t[10];
//  char t2[10];
//  sprintf(t, "%.2f %s", roundTo(f, 2), unit);
//  sprintf(t2, "%9s", t);
//  App.lcdPrint(16 - 9, 0, t2);
#endif

  tempStats.addValue(f);
  if (tempStats.changed) {
#if CONFIG_ENABLE_TFT_DISPLAY
    temperatureFrame.setDirty(true);
#endif
    LOGD(sensorName, "temp: " << f << " °" << unit);
  }
}

void TempSensor::markInvalidData() {
  LOGE(sensorName, "Error, invalid data...");
  tempStats.invalidSamples++;
}

void TempSensor::publishData() {
  LOGD(sensorName, "publishData called");

  if (tempStats.samples == 0.0) {
    LOGW(sensorName, "no temperature data to publish");
    return;
  }

  const size_t capacity = JSON_OBJECT_SIZE(4);
  DynamicJsonDocument doc(capacity);
  doc["sensor"] = (char*)sensorName.c_str();
  doc["temp"] = tempStats.getAverage(4);
  doc["unit"] = unit;
  if (hasHumiditySensor()) {
    doc["humidity"] = humidityStats.getAverage(2);
  } else {
    doc["humidity"] = nullptr;
  }

  Mqtt.publish(Mqtt.topics.temp, doc);

  tempStats.reset();
  humidityStats.reset();
}

#if CONFIG_ENABLE_I2C_OLED_DISPLAY_PLUGIN
void TempSensor::drawTemperatureFrame(OLEDDisplay *display,  OLEDDisplayUiState* state, int16_t x, int16_t y) {
  display->setFont(Roboto_Condensed_12);
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->drawString(x + 0, y + 0, "Temperature");
  display->setTextAlignment(TEXT_ALIGN_RIGHT);
  display->drawString(x + display->getWidth(), y + 0, sensorName);

  display->setFont(Roboto_Condensed_Bold_32);
  display->setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
  display->drawString(x + display->getWidth() / 2, y + display->getHeight() / 2, String(tempStats.current) + " °" + unit);
}

void TempSensor::drawHumidityFrame(OLEDDisplay *display,  OLEDDisplayUiState* state, int16_t x, int16_t y) {
  display->setFont(Roboto_Condensed_12);
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->drawString(x + 0, y + 0, "Humidity");
  display->setTextAlignment(TEXT_ALIGN_RIGHT);
  display->drawString(x + display->getWidth(), y + 0, sensorName);

  display->setFont(Roboto_Condensed_Bold_32);
  display->setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
  display->drawString(x + display->getWidth() / 2, y + display->getHeight() / 2, String(humidityStats.current) + " %");
}

void TempSensor::addFramesAndOverlays() {
//  App.getOled()->addFrame(
//      [this](OLEDDisplay *display,  OLEDDisplayUiState* state, int16_t x, int16_t y) {
//        drawTemperatureFrame(display, state, x, y);
//      }
//  );
//
//  if (hasHumiditySensor()) {
//    App.getOled()->addFrame(
//        [this](OLEDDisplay *display,  OLEDDisplayUiState* state, int16_t x, int16_t y) {
//          drawHumidityFrame(display, state, x, y);
//        }
//    );
//  }
}
#endif

#if CONFIG_ENABLE_TFT_DISPLAY
HumidityOverlay::HumidityOverlay(TempSensor *plugin)
    : StringDrawable(plugin, 7, &Roboto_Condensed_Bold_32, 0xF1D6) {
}
void HumidityOverlay::updateCurrent() {
  snprintf(current, strLength, "%.1f %%", plugin->humidityStats.current);
}
StringRenderInfo HumidityOverlay::getRenderInfo(TFT_eSPI *img, DisplayUI& ui, int16_t textWidth) {
  return StringRenderInfo(ui.maxX - textWidth, ui.maxY - img->glyph_ab); // NOLINT(modernize-return-braced-init-list)
}

TemperatureFrame::TemperatureFrame(TempSensor *plugin)
    : StringDrawable(plugin, 10, &Roboto_Condensed_Bold_82, 0xE228) {
}
void TemperatureFrame::updateCurrent() {
  snprintf(current, strLength, "%.1f %s", plugin->tempStats.current, plugin->unit);
}
StringRenderInfo TemperatureFrame::getRenderInfo(TFT_eSPI *img, DisplayUI& ui, int16_t textWidth) {
  return StringRenderInfo(ui.centerX - textWidth/2, ui.centerY - img->glyph_ab/2); // NOLINT(modernize-return-braced-init-list)
}

#endif
