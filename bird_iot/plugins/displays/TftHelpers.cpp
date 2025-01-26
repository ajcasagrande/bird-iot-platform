#include "TftHelpers.h"

#include "colors.h"

#if CONFIG_ENABLE_TFT_DISPLAY

void tftDrawString(TFT_eSPI *_img, char* text, char* prevText, int16_t x, int16_t y,
                   uint16_t fgColor, uint16_t bgColor, const GFXfont *f, bool includeBelowBaseline) {
  
  _img->setFreeFont(f);
  uint16_t first = pgm_read_word(&f->first);

  uint8_t xAdv = 0, prevXAdv = 0;
  GFXglyph *glyph, *prevGlyph;

  bool needsRefresh, sameWidth = true;
  uint32_t height = includeBelowBaseline ? _img->glyph_ab + _img->glyph_bb : _img->glyph_ab + 2;
  uint16_t len = strlen(text);
  uint16_t prevLen = prevText == nullptr ? 0 : strlen(prevText);

  // pad one character before
  if (bgColor != fgColor && prevLen > len) {
    // do not allow negative x values
    uint16_t _x = max(0, x-_img->glyph_xadv);
    // if there is less than xAdv space left, cap to available space
    uint16_t _w = min(_img->width() - _x, (int)_img->glyph_xadv);
    _img->fillRect(_x, y, _w, height, bgColor);
  }

  for (int i=0; i < len; i++) {
    needsRefresh = !(sameWidth && prevLen == len && text[i] == prevText[i]);

    glyph = &(((GFXglyph *)pgm_read_dword(&f->glyph))[(uint16_t)text[i] - first]);
    xAdv = pgm_read_byte(&glyph->xAdvance);
    // shrink spaces
    if (text[i] == ' ') {
      // todo, is this the right comparison?
      xAdv /= 2;
    }

    if (needsRefresh) {
      // overwrite previous char with background color
      if (sameWidth && i < prevLen) {
        prevGlyph = &(((GFXglyph *)pgm_read_dword(&f->glyph))[(uint16_t)prevText[i] - first]);
        prevXAdv = pgm_read_byte(&prevGlyph->xAdvance);
        if (prevText[i] == ' ') {
          prevXAdv /= 2;
        }

        if (prevXAdv != xAdv) {
          sameWidth = false;
          // todo: why is this needed? it seems counter intuitive?
          // if the width is different, then take the max of the previous and current
          // to make sure that we account for the whole character.
          _img->fillRect(x, y, max(prevXAdv, xAdv), height, bgColor);
        } else {
          // if the width is the same, just erase the previous width
          _img->fillRect(x, y, prevXAdv, height, bgColor);
        }

      } else {
        _img->fillRect(x, y, xAdv, height, bgColor);
      }
      // draw new char
      _img->drawChar(x, y + _img->glyph_ab, (uint16_t)text[i], fgColor, fgColor, 1);
    }
    // advance cursor
    x += xAdv;
  }

  // pad one character after
  if (bgColor != fgColor && prevLen > len) {
    // if there is less than xAdv space left, cap to available space
    uint16_t _w = min(_img->width() - x, (int)_img->glyph_xadv);
    _img->fillRect(x, y, _w, height, bgColor);
  }
}

int16_t tftMeasureString(TFT_eSPI *_img, char* text, const GFXfont *f) {
  _img->setFreeFont(f);

  uint16_t first = pgm_read_word(&f->first);
  uint16_t last = pgm_read_word(&f->last);

  uint16_t len = strlen(text);
  uint16_t uniCode = 0, n = 0;
  int16_t str_width = 0;
  while (n < len) {
    uniCode = _img->decodeUTF8((uint8_t*)text, &n, len - n);
    if (uniCode < first || uniCode > last) {
      continue;
    }
    GFXglyph *glyph  = &(((GFXglyph *)pgm_read_dword(&f->glyph))[uniCode - first]);
    if (n < len) {
      // if this is not the last character then use xAdvance
      str_width += pgm_read_byte(&glyph->xAdvance);
    } else { 
      // else use the offset plus width since this can be bigger than xAdvance
      str_width += ((int8_t)pgm_read_byte(&glyph->xOffset) + pgm_read_byte(&glyph->width));
    }
  }

  return str_width;
}

#endif // CONFIG_ENABLE_TFT_DISPLAY
