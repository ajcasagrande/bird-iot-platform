#pragma once

#include "sdkconfig.h"

#if CONFIG_ENABLE_TFT_DISPLAY

#include "include/builtin.h"
#include <TFT_eSPI.h>
#include "DisplayUI.h"
#include "TftHelpers.h"

struct StringRenderInfo {
  int16_t x;
  int16_t y;
  bool includeBelowBaseline = false;

  StringRenderInfo(int16_t x, int16_t y, bool includeBelowBaseline = false)
      : x(x), y(y), includeBelowBaseline(includeBelowBaseline) {
  }
};

class Drawable {
protected:
  bool _dirty = true;
  bool _forceRefresh = true;

public:
  virtual bool isDirty() { return _dirty; }
  void setDirty(bool dirty) { _dirty = dirty; }
  virtual bool isForceRefresh() { return _forceRefresh; }
  void setForceRefresh(bool force) { _forceRefresh = force; }

  // Pure-virtual
  virtual void draw(TFT_eSPI *img, DisplayUI& ui) = 0;
};

template<typename T>
class StringDrawable : public Drawable {
public:
  explicit StringDrawable(T *plugin, size_t strLength, const GFXfont *font, uint16_t fontColor)
        : plugin(plugin), strLength(strLength), font(font), fontColor(fontColor) {

    prev = (char*) malloc(strLength * sizeof(char));
    current = (char*) malloc(strLength * sizeof(char));
  }

  ~StringDrawable() {
    free(prev);
    free(current);
  }

  virtual void setCurrent(const char *str) {
    strncpy(current, str, strLength);
  }

  virtual void updateCurrent() = 0;
  virtual StringRenderInfo getRenderInfo(TFT_eSPI *img, DisplayUI& ui, int16_t textWidth) = 0;

  void draw(TFT_eSPI *img, DisplayUI& ui) override {
    updateCurrent();

    if (!isForceRefresh() && strcmp(current, prev) == 0) {
      return;
    }

    StringRenderInfo pt = getRenderInfo(img, ui, tftMeasureString(img, current, font));
    tftDrawString(img, current, isForceRefresh() ? nullptr : prev,
                  pt.x, pt.y,
                  fontColor, ui.bgColor, font,
                  pt.includeBelowBaseline);

    strncpy(prev, current, strLength);
  }

protected:
  T *plugin;
  size_t strLength;
  char* prev = nullptr;
  char* current = nullptr;
  const GFXfont *font;
  uint16_t fontColor;
};

#endif // CONFIG_ENABLE_TFT_DISPLAY
