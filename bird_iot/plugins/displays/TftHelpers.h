#pragma once
#include "sdkconfig.h"

#if CONFIG_ENABLE_TFT_DISPLAY
#include "builtin.h"
#include <TFT_eSPI.h>


void tftDrawString(TFT_eSPI *_img, char* text, char* prevText, int16_t x, int16_t y,
                                          uint16_t fgColor, uint16_t bgColor, const GFXfont *f, bool includeBelowBaseline = false);

int16_t tftMeasureString(TFT_eSPI *_img, char* text, const GFXfont *f);

#endif // CONFIG_ENABLE_TFT_DISPLAY
