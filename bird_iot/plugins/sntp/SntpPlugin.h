#pragma once

#include "sdkconfig.h"

#if CONFIG_ENABLE_SNTP_PLUGIN

#include "common.h"
#include "DisplayManager.h"
#if CONFIG_ENABLE_TFT_DISPLAY
#include "TFTDisplayPlugin.h"
#include "fonts/dialoginput.h"
#include "fonts/dejavu_sans.h"
#endif // CONFIG_ENABLE_TFT_DISPLAY

class SntpPlugin : public IotPlugin
#if CONFIG_ENABLE_TFT_DISPLAY
    , public Drawable
#endif
    {
public:
  SntpPlugin();

  void setSynched(bool synched) { _synched = synched; }
  bool synched() { return _synched; }

  bool setup() override;
//  bool start() override;
  void onWifiConnected() override;
//  void onWifiDisconnected() override;
//  void onMqttConnected() override;
//  void onMqttDisconnected() override;
//  bool handleMqttMessage(const char *topic, int id, const char *cmd, const JsonDocument& json) override;
  bool handleCommand(const std::string& cmd) override;
#if CONFIG_ENABLE_I2C_OLED_DISPLAY_PLUGIN
//  void addFramesAndOverlays() override;o
#endif
#if CONFIG_ENABLE_TFT_DISPLAY
  void draw(TFT_eSPI *img, DisplayUI& ui) override;
#endif
  static char* printTime();
  VoidTask *task;

#if CONFIG_ENABLE_TFT_DISPLAY
  const static size_t strLength = 13;
  char prev[strLength] = "\0";
  char current[strLength] = "\0";
  const uint16_t fontColor = TFT_WHITE; // 0x0492; // 0x47EA; // 0xF813;
  const GFXfont *font = &DejaVu_Sans_32;
#if CONFIG_TFT_SNTP_LARGE_DISPLAY_SECONDS
  const GFXfont *largeFont = &DejaVu_Sans_32;
#else
  const GFXfont *largeFont = &DejaVu_Sans_72;
#endif // CONFIG_TFT_SNTP_LARGE_DISPLAY_SECONDS

#endif // CONFIG_ENABLE_TFT_DISPLAY

private:
  bool _synched = false;
};

extern SntpPlugin Sntp;

#endif // CONFIG_ENABLE_SNTP_PLUGIN
