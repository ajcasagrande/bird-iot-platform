#pragma once
#include "sdkconfig.h"

#include "include/builtin.h"
#include "include/common.h"

#if CONFIG_ENABLE_I2C_OLED_DISPLAY_PLUGIN
#include <OLEDDisplay.h>
#include <OLEDDisplayUi.h>
#endif

class TempSensor;

#if CONFIG_ENABLE_TFT_DISPLAY
#include "TFTDisplayPlugin.h"
#include "DisplayManager.h"
#include "fonts/roboto_condensed.h"

class HumidityOverlay : public StringDrawable<TempSensor> {
public:
  explicit HumidityOverlay(TempSensor *plugin);
  void updateCurrent() override;
  StringRenderInfo getRenderInfo(TFT_eSPI *img, DisplayUI& ui, int16_t textWidth) override;
};

class TemperatureFrame : public StringDrawable<TempSensor> {
public:
  explicit TemperatureFrame(TempSensor *plugin);
  void updateCurrent() override;
  StringRenderInfo getRenderInfo(TFT_eSPI *img, DisplayUI& ui, int16_t textWidth) override;
};

#endif


class TempSensor : public BaseSensor {
public:
  const char* unit;

protected:
  uint32_t _readInterval = CONFIG_TEMP_SENSOR_READ_INTERVAL;
  uint32_t _publishInterval = CONFIG_TEMP_SENSOR_PUBLISH_INTERVAL;
  float maxValidTemp = 200.0;
  float minValidTemp = -10.0;

  void addValues(float, float);
  void addTempValue(float);
  void markInvalidData();

#if CONFIG_ENABLE_TFT_DISPLAY
  HumidityOverlay humidityOverlay;
  TemperatureFrame temperatureFrame;
#endif

public:
  explicit TempSensor(const std::string& sensorName)
      : BaseSensor(sensorName + " Temp Sensor", sensorName), unit("F")
#if CONFIG_ENABLE_TFT_DISPLAY
      , humidityOverlay(this), temperatureFrame(this)
#endif
  { }

  FloatStats tempStats = FloatStats("Temp");
  FloatStats humidityStats = FloatStats("Humidity");

#if CONFIG_ENABLE_I2C_OLED_DISPLAY_PLUGIN
  void drawTemperatureFrame(OLEDDisplay *display,  OLEDDisplayUiState* state, int16_t x, int16_t y);
  void drawHumidityFrame(OLEDDisplay *display,  OLEDDisplayUiState* state, int16_t x, int16_t y);
  void addFramesAndOverlays() override;
#endif

  void publishData() override;
  bool setup() override;

  virtual bool hasHumiditySensor() = 0;

  static bool validateHumidity(float h);
  bool validateTemp(float f);
};
