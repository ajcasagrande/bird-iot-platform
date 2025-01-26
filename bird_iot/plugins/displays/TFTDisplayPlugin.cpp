#include "TFTDisplayPlugin.h"
#if CONFIG_ENABLE_TFT_DISPLAY

#include "DeviceIdOverlay.h"
#include "VoltageOverlay.h"
#include "TftHelpers.h"

#define DEFAULT_ROTATION 3

TFTDisplayPlugin TFTDisplay;
DisplayManager TFTDisplayManager;

static const char* TAG = "TFT";

void _render(TFTDisplayPlugin *plugin) {
  plugin->render();
}

TFTDisplayPlugin::TFTDisplayPlugin() : IotPlugin("TFT Display Plugin") {
  manager = &TFTDisplayManager;
  task = new Task<TFTDisplayPlugin>("TFT Display", this, _render);
}

void TFTDisplayPlugin::setBacklight(uint8_t percent) {
  backlightPercent = percent;
  sigmaDeltaWrite(pwmBacklight, (int)((int)percent / 100.0 * 255.0));
}

bool TFTDisplayPlugin::setup() {
  LOGD(TAG, "setup tft display plugin");
  LOGD(TAG, "tft width: " << TFT_WIDTH);
  LOGD(TAG, "tft height: " << TFT_HEIGHT);

  tft = new TFT_eSPI();

  tft->init();
  // Rotation 1 = widescreen usb port on right
  // Rotation 3 = widescreen usb port on left
  tft->setRotation(Prefs.getUint8(PREF_TFT_ROTATION, DEFAULT_ROTATION));
  tft->fillScreen(ui.bgColor);

#if TFT_BL > 0
    pinMode(TFT_BL, OUTPUT);
    // todo: sigma delta should be a plugin that you can request the next available channel
    // https://github.com/espressif/arduino-esp32/blob/master/libraries/ESP32/examples/AnalogOut/SigmaDelta/SigmaDelta.ino
    // todo: should probably actually use ledC
    sigmaDeltaSetup(pwmBacklight, 312500);
    sigmaDeltaAttachPin(TFT_BL, pwmBacklight);
    setBacklight(backlightPercent); // todo: make this KConfig
#endif

#if CONFIG_ENABLE_TFT_BUFFER
  img = new TFT_eSprite(tft);
  // swap height and width because we are rotating screen
  img->createSprite(TFT_HEIGHT, TFT_WIDTH);
#else
  img = tft;
#endif

  tft->setTextWrap(false, false);
  img->setTextWrap(false, false);
  fill(ui.bgColor);

  TFTDisplayManager.registerOverlay(new DeviceIdOverlay());
  TFTDisplayManager.registerOverlay(new VoltageOverlay());

  // add extra for sprintf
  return task->configure(1000 / CONFIG_TFT_LCD_UI_FPS, _2k, MEDIUM_LOW_PRIORITY, true, false);
}

bool TFTDisplayPlugin::start() {
  return task->start();
}

void TFTDisplayPlugin::fill(uint32_t color) {
#if CONFIG_ENABLE_TFT_BUFFER
  img->fillSprite(color);
#else
  tft->fillScreen(color);
#endif
}

void TFTDisplayPlugin::pushSprite() {
#if CONFIG_ENABLE_TFT_BUFFER
  img->pushSprite(0, 0);
#endif
}

void TFTDisplayPlugin::render() {
  if (rotationRequested) {
    toggleRotationInternal();
  }

  manager->render();
}

void TFTDisplayPlugin::drawScreensaver() {
  static TFT_eSprite* sprite = nullptr;
  static int16_t maxWidth = 0;

  if (!ui.isPaused()) {
    if (maxWidth == 0) {
      img->setTextSize(2);
      img->setTextFont(1);
      maxWidth = img->textWidth(deviceId());
      sprite = new TFT_eSprite(tft);
      sprite->createSprite(abs(ui.xVelocity) + maxWidth, abs(ui.yVelocity) + tft->fontHeight());
      sprite->setTextSize(2);
      sprite->setTextFont(1);
      sprite->setTextDatum(TL_DATUM);
      LOGD(TAG, "Screensaver sprite memory usage: " << sizeof(*sprite) << " bytes");
    }

    // clear out the old one
    sprite->fillSprite(ui.bgColor);

    // set this up here because we do not want to change colors until _after_ we hit the wall
    sprite->setTextColor(ui.fontColor);

    ui.x += ui.xVelocity;
    ui.y += ui.yVelocity;

    if (ui.x >= ui.width - maxWidth || ui.x <= 0) {
      ui.xVelocity *= -1;
      ui.fontColor = randomColor();
    }
    if (ui.y >= ui.height - img->fontHeight() || ui.y <= 0) {
      ui.yVelocity *= -1;
      ui.fontColor = randomColor();
    }

    // if the velocity is positive, text will be offset inside the sprite
    sprite->setCursor(max((int8_t)0, ui.xVelocity), max((int8_t)0, ui.yVelocity));
    sprite->print(deviceId());
    // if the velocity is negative, the sprite will be offset
    sprite->pushSprite(ui.x + min((int8_t)0, ui.xVelocity), ui.y + min((int8_t)0, ui.yVelocity));
  }
}

void TFTDisplayPlugin::drawProgress(uint8_t percent, const String& strTop, const String& strBottom) {
  ui.pause();
  ui.progress = percent;

  uint16_t barHeight = 30;
  uint16_t barPadding = 10;
  uint16_t barY = ui.centerY - (barHeight / 2);

  fill(ui.progressBgColor);

  int16_t textWidth = tftMeasureString(img, (char *)strTop.c_str(), ui.progressFont);
  tftDrawString(img, (char *)strTop.c_str(), nullptr, ui.centerX - textWidth/2, barY / 2 - img->glyph_ab / 2,
      ui.progressTopTextColor, ui.progressBgColor, ui.progressFont, true);

  // only draw first time
  img->drawRoundRect(barPadding, barY, ui.width - (barPadding * 2), barHeight, 15, ui.progressLineColor);

  drawProgressBar(barPadding, barY, ui.width - (barPadding * 2), barHeight, percent);

  textWidth = tftMeasureString(img, (char *)strBottom.c_str(), ui.progressFont);
  tftDrawString(img, (char *)strBottom.c_str(), nullptr, ui.centerX - textWidth/2, barY + 20 + barHeight,
      ui.progressBottomTextColor, ui.progressBgColor, ui.progressFont);

  TFTDisplay.pushSprite();
}

void TFTDisplayPlugin::updateProgress(uint8_t percent, char* strTop, char* strBottom, char* prev) {
  static const uint16_t barHeight = 30;
  static const uint16_t barPadding = 10;
  static uint16_t barY = ui.centerY - (barHeight / 2);

  int16_t textWidth;
  int16_t x, y;

  ui.pause();
  ui.progress = percent;

  if (strTop != nullptr) {
    textWidth = tftMeasureString(img, strTop, ui.progressFont);
    x = ui.centerX - textWidth / 2;
    y = barY / 2 - img->glyph_ab / 2;
    img->fillRect(0, y, x - 0, img->glyph_ab + img->glyph_bb, ui.progressBgColor);
    img->fillRect(x + textWidth, y, ui.maxX - (x + textWidth), img->glyph_ab + img->glyph_bb, ui.progressBgColor);
    tftDrawString(img, strTop, nullptr, x, y,
                  ui.progressTopTextColor, ui.progressBgColor, ui.progressFont, true);
  }

  drawProgressBar(barPadding, barY, ui.width - (barPadding * 2), barHeight, percent);

  if (strBottom != nullptr) {
    textWidth = tftMeasureString(img, strBottom, ui.progressFont);
    tftDrawString(img, strBottom, prev, ui.centerX - textWidth / 2,
                  barY + barHeight + ((ui.maxY - (barY + barHeight)) / 2) - img->glyph_ab / 2,
                  ui.progressBottomTextColor, ui.progressBgColor, ui.progressFont);
  }
}

void TFTDisplayPlugin::drawProgressBar(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t percent) {
  static const uint8_t margin = 2;
  uint16_t barHeight = h - 2 * margin;
  uint16_t barWidth  = w - 2 * margin;
  uint16_t pWidth = barWidth * percent / 100.0;
  img->fillRoundRect(x + margin, y + margin, pWidth, barHeight, 10, ui.progressFillColor);
}

void TFTDisplayPlugin::toggleRotation() {
  rotationRequested = true;
  if (task->isPaused()) {
    toggleRotationInternal();
  }
}

void TFTDisplayPlugin::toggleRotationInternal() {
  uint8_t rot = tft->getRotation() == 3 ? 1 : 3;
  Prefs.setUint8(PREF_TFT_ROTATION, rot);
  tft->setRotation(rot);
  fill(ui.bgColor);
  manager->forceRefreshAll();
  rotationRequested = false;
}

void TFTDisplayPlugin::toggleDisplay() {
  // todo: how to implement?
}

void TFTDisplayPlugin::increaseBacklight(int step, bool wrap) {
  if (backlightPercent == 100) {
    if (wrap) {
      backlightPercent = step;
    }
  } else {
    backlightPercent += step;
    if (backlightPercent > 100) {
      backlightPercent = 100;
    }
  }

  setBacklight(backlightPercent);
}

#endif // CONFIG_ENABLE_TFT_DISPLAY
