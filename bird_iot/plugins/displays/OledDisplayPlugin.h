#pragma once
#include "sdkconfig.h"

#if CONFIG_ENABLE_I2C_OLED_DISPLAY_PLUGIN

#include "include/builtin.h"
#include "IotPlugin.h"
#include "tasks/TaskClass.h"

#include <SSD1306Wire.h>
#include <OLEDDisplayUi.h>

class OledDisplayPlugin : public IotPlugin {
private:
  uint8_t address;
  SSD1306Wire *_display;
  OLEDDisplayUi *ui;

  std::vector<FrameCallback> frames;
  std::vector<OverlayCallback> overlays;
  Task<OledDisplayPlugin> *task;

public:
  explicit OledDisplayPlugin(uint8_t address);
  ~OledDisplayPlugin();

  void drawProgress(uint8_t percent, String strTop, String strBottom);

  void addFrame(FrameCallback frame);
  void addOverlay(OverlayCallback overlay);

  bool setup() override;
  bool start() override;
  void execute();
};

#endif // CONFIG_ENABLE_I2C_OLED_DISPLAY_PLUGIN

