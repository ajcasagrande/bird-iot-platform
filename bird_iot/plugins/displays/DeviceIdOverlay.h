#pragma once

#include "sdkconfig.h"
#if CONFIG_ENABLE_TFT_DISPLAY

#include "builtin.h"
#include "Drawable.h"

#include "fonts/roboto.h"

class DeviceIdOverlay : public Drawable {
public:
  void draw(TFT_eSPI *img, DisplayUI& ui) override;

  const GFXfont *font = &Roboto_Bold_18;
};
#endif // CONFIG_ENABLE_TFT_DISPLAY
