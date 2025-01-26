#include "VoltageOverlay.h"
#include "sdkconfig.h"

#if CONFIG_ENABLE_TFT_DISPLAY

#include "helpers.h"
#include "logging.h"
#include "TftHelpers.h"
#include "xprintf.h"

void VoltageOverlay::draw(TFT_eSPI *img, DisplayUI& ui) {
  img->setFreeFont(font);

  double vcc = readVcc();
  int iv = (int)vcc;
  double fv = vcc - iv;
  int f1 = (int)(fv * 10);
  int f2 = (int)(fv*100) - (f1*10);

  // example: 7.44v
  char vccStr[6] = {
      (char)('0' + iv),
      '.',
      (char)('0' + f1),
      (char)('0' + f2),
      'v',
      '\0'
  };

  int16_t textWidth = tftMeasureString(img, vccStr, font);
  tftDrawString(img, vccStr, nullptr, ui.maxX - textWidth, ui.maxY - img->glyph_ab - img->glyph_bb, 0xB5B6, ui.bgColor, font, true);
}

#endif // CONFIG_ENABLE_TFT_DISPLAY
