#include "SntpPlugin.h"
#if CONFIG_ENABLE_SNTP_PLUGIN

#include <cstdlib>
#include <ctime>
#include <lwip/apps/sntp.h>
#if CONFIG_ENABLE_TFT_DISPLAY
#include "TFTDisplayPlugin.h"
#include "TftHelpers.h"
#endif

static const char* TAG = "SNTP";

SntpPlugin Sntp;

SntpPlugin::SntpPlugin() : IotPlugin("SNTP Plugin") {
}

static void _execute() {
#if CONFIG_ENABLE_TFT_DISPLAY
  Sntp.setDirty(true);
#endif
}

void time_sync_notification_cb(struct timeval *tv) {
  if (!Sntp.synched()) {
#if CONFIG_ENABLE_TFT_DISPLAY
    Sntp.setForceRefresh(true);
#endif
    Sntp.setSynched(true);

    // set the initial delay to exactly how many milliseconds left before the next second
    Sntp.task->setInitialDelay(1000 - (tv->tv_usec / 1000));
    // start the task
    Sntp.task->start();

    LOGI(TAG, "Starting sntp task");
  }

  LOGI(TAG, "Notification of a time synchronization event");
  SntpPlugin::printTime();
#if CONFIG_ENABLE_TFT_DISPLAY
  Sntp.setDirty(true);
#endif

}

bool SntpPlugin::setup() {
#if CONFIG_ENABLE_TFT_DISPLAY
  TFTDisplayManager.registerOverlay(this);
#endif
  task = new VoidTask("Sntp", _execute);
  return task->configure(1000, _0p75, MEDIUM_HIGH_PRIORITY, tskNO_AFFINITY, true, false);
  // DO NOT Start the task yet! wait until first time sync!
}

void SntpPlugin::onWifiConnected() {
  if (sntp_enabled()) {
    LOGD(TAG, "stopping existing sntp");
    sntp_stop();
  }
  LOGI(TAG, "configuring time using sntp");

  sntp_setoperatingmode(SNTP_OPMODE_POLL);
  sntp_setservername(0, (char*)CONFIG_NTP_SERVER_1);
  sntp_setservername(1, (char*)CONFIG_NTP_SERVER_2);
  LOGI(TAG, "Server 1: " << CONFIG_NTP_SERVER_1);
  LOGI(TAG, "Server 2: " << CONFIG_NTP_SERVER_2);

  sntp_set_time_sync_notification_cb(time_sync_notification_cb);
  sntp_set_sync_mode(SNTP_SYNC_MODE_IMMED);
  sntp_init();

  LOGI(TAG, "TZ: " << CONFIG_TIMEZONE_CODE);
  setenv("TZ", CONFIG_TIMEZONE_CODE, 1);
  tzset();
  LOGD(TAG, "sntp configuration complete");
}

char* SntpPlugin::printTime() {
  static time_t now;
  static struct tm timeinfo;
  static char strftime_buf[30];
  time(&now);
  localtime_r(&now, &timeinfo);
  strftime(strftime_buf, sizeof(strftime_buf), "%c", &timeinfo);
  LOGI(TAG, "The current date/time is: " << strftime_buf);
  return strftime_buf;
}

//  void SntpPlugin::onWifiDisconnected() { }
//  void SntpPlugin::onMqttConnected() { }
//  void SntpPlugin::onMqttDisconnected() { }
//  bool SntpPlugin::handleMqttMessage(const char *topic, int id, const char *cmd, const JsonDocument& json) {
//   return false; // false means not handled 
// }
bool SntpPlugin::handleCommand(const std::string& cmd) {
  if (cmd == "time" || cmd == "date") {
    printTime();
    return true;
  }
  return false;
}

#if CONFIG_ENABLE_TFT_DISPLAY
void SntpPlugin::draw(TFT_eSPI *img, DisplayUI& ui) {
  static struct tm t;
  static time_t now;
//  static int16_t len;

  if (!synched()) {
    memset(&t, 0, sizeof(t));
  } else {
    time(&now);
    localtime_r(&now, &t);
  }

  if (TFTDisplayManager.hasFrames()) {
    strftime(current, strLength, "%l:%M:%S %p", &t);
  } else {
    strftime(current, strLength,
#if CONFIG_TFT_SNTP_LARGE_DISPLAY_SECONDS
        "%l:%M:%S %p"
#else
        "%l:%M"
#endif
        , &t);

//    len = strlen(current);
//    current[len] = ' ';
//    current[len+1] = t.tm_hour >= 12 ? 'P' : 'A';
  }

  char *time = current[0] == ' ' ? current + 1 : current;
  if (!isForceRefresh() && strcmp(time, prev) == 0) {
    return;
  }

  int16_t textWidth, x, y;
  const GFXfont *_font;

  if (TFTDisplayManager.hasFrames()) {
    _font = font;
    textWidth = tftMeasureString(img, time, _font);
    x = ui.centerX - textWidth / 2;
    y = 0;
  } else {
    _font = largeFont;
    textWidth = tftMeasureString(img, time, _font);
    x = ui.centerX - textWidth / 2;
    y = ui.centerY - img->glyph_ab/2 - img->glyph_bb/2;
  }

  if (isForceRefresh()) {
    img->fillRect(0, y, img->width(), img->glyph_ab + 2, ui.bgColor);
  }
  tftDrawString(img, time, isForceRefresh() ? nullptr : prev, x, y, fontColor, ui.bgColor, _font);
  strcpy(prev, time);

}
#endif

#if ENABLE_I2C_OLED_DISPLAY_PLUGIN
//  void SntpPlugin::addFramesAndOverlays() { }
#endif

#endif // CONFIG_ENABLE_SNTP_PLUGIN
