#pragma once

#include <vector>
#include <cstdint>
#include "Drawable.h"

#if CONFIG_ENABLE_TFT_DISPLAY

class DisplayManager {
protected:
  std::vector<Drawable*> frames;
  std::vector<Drawable*> overlays;

public:
  DisplayManager() = default;
  explicit DisplayManager(uint16_t bgColor) : bgColor(bgColor) { }

  int frameIndex = 0;
  uint16_t bgColor = TFT_BLACK;

  void registerFrame(Drawable *frame) { frames.push_back(frame); }
  void registerOverlay(Drawable *overlay) { overlays.push_back(overlay); }

  void next();
  void render();

  void forceRefreshAll();
  bool hasFrames();
};

#endif

