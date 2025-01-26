#include "DeviceIdOverlay.h"
#include "sdkconfig.h"

#if CONFIG_ENABLE_TFT_DISPLAY

#include "logging.h"
#include "helpers.h"
#include "TftHelpers.h"

void DeviceIdOverlay::draw(TFT_eSPI *img, DisplayUI& ui) {
  img->setFreeFont(font);
  LOGI("DeviceIdOverlay", deviceId());
  tftDrawString(img, (char *)deviceId(), nullptr, 0, ui.maxY - img->glyph_ab - img->glyph_bb, 0xB5B6, ui.bgColor, font, true);
}

#endif // CONFIG_ENABLE_TFT_DISPLAY
