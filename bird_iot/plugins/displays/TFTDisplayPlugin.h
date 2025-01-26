#pragma once
#include "sdkconfig.h"

#if CONFIG_ENABLE_TFT_DISPLAY
#include "include/common.h"

#include <TFT_eSPI.h>
#include <SPI.h>
#include "DisplayManager.h"

#define GXFF 1

class TFTDisplayPlugin : public IotPlugin {
private:
  TFT_eSPI *tft;

#if CONFIG_ENABLE_TFT_BUFFER
  TFT_eSprite *img;
#else
  TFT_eSPI *img;
#endif

  uint8_t pwmBacklight = 0;
  uint8_t backlightPercent = 20;
  DisplayUI ui;
  DisplayManager *manager;

  bool rotationRequested = false;
  void toggleRotationInternal();

public:
  TFTDisplayPlugin();

  bool setup() override;
  bool start() override;
  void setBacklight(uint8_t percent);
  void render();

  TFT_eSPI* getSprite() { return img; }

  Task<TFTDisplayPlugin> *task;
  DisplayUI& getUI() { return ui; }
  DisplayManager* getManager() { return manager; }
  void setManager(DisplayManager* displayManager) {
    manager = displayManager;
    ui.bgColor = manager->bgColor;
  }

  void drawProgressBar(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t percent);
  void drawProgress(uint8_t percent, const String& strTop, const String& strBottom);
  void updateProgress(uint8_t percent, char* strTop, char* strBottom, char* prev);

  void drawScreensaver();

  void fill(uint32_t color);
  void pushSprite();

  void toggleRotation();
  void toggleDisplay();
  void increaseBacklight(int step, bool wrap = true);
};

extern DisplayManager TFTDisplayManager;
extern TFTDisplayPlugin TFTDisplay;

#endif // CONFIG_ENABLE_TFT_DISPLAY
