#pragma once

#include "sdkconfig.h"

#if CONFIG_ENABLE_TFT_DISPLAY

#include <cstdint>
#include "colors.h"
#include "TFT_eSPI.h"
#include "roboto_condensed.h"

class DisplayUI {
public:
  volatile bool paused = false;

  uint8_t progress = 0;
  int16_t x = 0;
  int16_t y = 0;
  int8_t xVelocity = 1;
  int8_t yVelocity = 1;
  uint8_t font = 2;

  // rotated sizes (width, height) are opposite
  int16_t width = TFT_HEIGHT;
  int16_t height = TFT_WIDTH;

  int16_t centerX = width / 2;
  int16_t centerY = height / 2;

  int16_t maxX = width - 1;
  int16_t maxY = height - 1;

  uint16_t bgColor =
//      color565(43, 43, 43);
      COLOR_BLACK;
//      COLOR_DARKGREY;
  uint16_t fontColor = COLOR_WHITE;
  uint16_t progressBgColor = COLOR_BLACK;
  uint16_t progressLineColor = COLOR_CYAN;
  uint16_t progressFillColor = COLOR_DARKCYAN;
  uint16_t progressTopTextColor = COLOR_WHITE;
  uint16_t progressBottomTextColor = COLOR_WHITE;

  const GFXfont *progressFont = &Roboto_Condensed_Bold_26;

  void pause() { paused = true; }
  void resume() { paused = false; }
  bool isPaused() { return paused; }
};

#endif // CONFIG_ENABLE_TFT_DISPLAY
