#include "DisplayManager.h"

#if CONFIG_ENABLE_TFT_DISPLAY

#include "logging.h"
#include "TFTDisplayPlugin.h"


static const char* TAG = "Display";

void DisplayManager::next() {
  if (++frameIndex >= frames.size()) {
    frameIndex = 0;
  }
  // force a refresh
  frames[frameIndex]->setForceRefresh(true);
  frames[frameIndex]->setDirty(true);
}

void DisplayManager::render() {
  if (frames.size() > 1) {
    // todo: let the frames dictate how long they want to be shown
    if ((TFTDisplay.task->_iterations) % (10000 / TFTDisplay.task->_interval) == 0) {
      LOGD(TAG, "next frame called");
      next();
    }
  }

  if (frames.size() > frameIndex) {
    if (frames[frameIndex]->isDirty() || frames[frameIndex]->isForceRefresh()) {
      frames[frameIndex]->setDirty(false); // do this first to prevent race conditions if it gets dirty while we are drawing it
      frames[frameIndex]->draw(TFTDisplay.getSprite(), TFTDisplay.getUI());
      frames[frameIndex]->setForceRefresh(false); // do this after so the draw method is able to query it as well
    }
  }

  for (auto & overlay : overlays) {
    if (overlay->isDirty() || overlay->isForceRefresh()) {
      overlay->setDirty(false);
      overlay->draw(TFTDisplay.getSprite(), TFTDisplay.getUI());
      overlay->setForceRefresh(false);
    }
  }
}

bool DisplayManager::hasFrames() {
  return !frames.empty();
}

void DisplayManager::forceRefreshAll() {
  for (auto & frame : frames) {
    frame->setForceRefresh(true);
  }
  for (auto & overlay : overlays) {
    overlay->setForceRefresh(true);
  }
}

#endif
