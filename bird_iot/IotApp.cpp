#include "IotApp.h"

#include <esp_ota_ops.h>
#include "include/common.h"
#include "include/version.h"
#include "include/plugins_inc.h"
#include "include/rtos.h"

IotApp App;

static const char* TAG = "App";

bool IotApp::setup() {
  LOGI(TAG, "IotApp initializing...");

  bist();

  profile = *findProfile();
  if (profile.id != UNKNOWN_PROFILE) {
    LOGI(TAG, "Found profile: " << profile.id);
  } else {
    LOGW(TAG, "WARNING: no profile found for deviceId: " << deviceId());
  }

  return true;
}

void IotApp::registerPlugin(IotPlugin* plugin) {
  LOGI(TAG, "Register plugin: " << plugin->name);
  plugins.push_back(plugin);
  // In the case where plugins are already setup, call setup
  if (_pluginsSetup) {
    LOGI(TAG, "Setup plugin: " << plugin->name);
    plugin->setup();
  }
  if (_setupComplete) {
    LOGI(TAG, "Start plugin: " << plugin->name);
    plugin->start();
  }
}

bool IotApp::bist() {
  LOGI(TAG, "Software version: " << SOFTWARE_VERSION);
  LOGI(TAG, "Software revision: " << SOFTWARE_REVISION);
  LOGD(TAG, "CPU Freq: " << ESP.getCpuFreqMHz());
  LOGD(TAG, "CPU Cores: " << portNUM_PROCESSORS);
  LOGD(TAG, "Chip Revision: 0x" << _HEX(ESP.getChipRevision()));
  return true;
}

bool IotApp::setupPlugins() {
  bool result = true;
  IotPlugin *plugin;

  LOGI(TAG, "Setup plugins...");

  auto it = plugins.begin();
  while (it != plugins.end()) {
    plugin = *it;

    LOGI(TAG, "Initialize plugin: " << plugin->name << "...");
    uint32_t start = millis();
    bool success = plugin->setup() && verifyHeap();

    if (success) {
      LOGI(TAG, plugin->name << "... OK (" << since(start) << " ms)");
      it++;
    } else {
      LOGE(TAG, plugin->name << "... FAIL (" << since(start) << " ms)");
      LOGE(TAG, "De-registering plugin " << plugin->name);
      it = plugins.erase(it);
    }
    result = result && success;
  }

#if CONFIG_ENABLE_I2C_OLED_DISPLAY_PLUGIN
  if (oled != nullptr) {
    for (auto & p : plugins) {
      p->addFramesAndOverlays();
    }
  }
#endif

#ifdef CONFIG_APP_ROLLBACK_ENABLE
  if (!result) {
    IotApp::performRollback();
  }
#endif

  _pluginsSetup = true;

  return result;
}

bool IotApp::startPlugins() {
  bool result = true;
  IotPlugin *plugin;

  LOGI(TAG, "Start plugins...");

  auto it = plugins.begin();
  while (it != plugins.end()) {
    plugin = *it;

    LOGI(TAG, "Start plugin: " << plugin->name << "...");
    uint32_t start = millis();
    bool success = plugin->start() && verifyHeap();

    if (success) {
      LOGI(TAG, plugin->name << "... OK (" << since(start) << " ms)");
      it++;
    } else {
      LOGE(TAG, plugin->name << "... FAIL (" << since(start) << " ms)");
      LOGE(TAG, "De-registering plugin " << plugin->name);
      it = plugins.erase(it);
    }
    result = result && success;
  }

#ifdef CONFIG_APP_ROLLBACK_ENABLE
  if (!result) {
    IotApp::performRollback();
  }
#endif

  _setupComplete = true;
  return result;
}

#ifdef CONFIG_APP_ROLLBACK_ENABLE
void IotApp::performRollback() {
  const esp_partition_t *running = esp_ota_get_running_partition();
  esp_ota_img_states_t ota_state;
  if (esp_ota_get_state_partition(running, &ota_state) == ESP_OK) {
    if (ota_state == ESP_OTA_IMG_PENDING_VERIFY || ota_state == ESP_OTA_IMG_NEW) {
      LOGE(TAG, "OTA verification failed! Start rollback to the previous version...");
      Device.sendAlertWithReason(ALERT_OTA_ROLLBACK, "one or more plugins failed their setup function");
      taskDELAY(3000);
      esp_ota_mark_app_invalid_rollback_and_reboot();
    }
  }
}
#endif

#if CONFIG_ENABLE_I2C_LCD_CHARACTER_DISPLAY
void IotApp::registerLcd(LcdDriver* driver) {
  if (lcdDriver == nullptr) {
    registerPlugin(driver);
  } else {
    LOGW(TAG, "warning, lcd driver already registered. replacing existing one.");
  }
  lcdDriver = driver;
}
#endif

#if CONFIG_ENABLE_NEOPIXEL_DRIVER
void IotApp::registerNeoPixel(NeoPixelDriver* neoPixelDriver) {
  neoPixel = neoPixelDriver;
  registerPlugin(neoPixelDriver);
}
#endif

#if CONFIG_ENABLE_I2C_OLED_DISPLAY_PLUGIN
void IotApp::registerOledDisplay(OledDisplayPlugin *oledDisplayPlugin) {
  oled = oledDisplayPlugin;
  registerPlugin(oled);
}
#endif

void IotApp::setStatusColor(RGB color) {
#if CONFIG_ENABLE_NEOPIXEL_DRIVER
  if (neoPixel != nullptr) {
    neoPixel->setAll(color);
  }
#endif
}

void IotApp::drawProgress(uint8_t percent, const String& strTop, const String& strBottom) {
  if (SafeMode.isActive()) { return; }

#if CONFIG_ENABLE_TFT_DISPLAY
  TFTDisplay.drawProgress(percent, strTop, strBottom);
#endif
#if CONFIG_ENABLE_I2C_OLED_DISPLAY_PLUGIN
  if (oled != nullptr) {
    oled->drawProgress(percent, std::move(strTop), std::move(strBottom));
  }
#endif
}

void IotApp::updateProgress(uint8_t percent, char* strTop, char* strBottom, char* prev) {
  if (SafeMode.isActive()) { return; }

#if CONFIG_ENABLE_TFT_DISPLAY
  TFTDisplay.updateProgress(percent, strTop, strBottom, prev);
#endif
#if CONFIG_ENABLE_I2C_OLED_DISPLAY_PLUGIN
  if (oled != nullptr) {
    oled->drawProgress(percent, "", strBottom);
  }
#endif
}

#if CONFIG_ENABLE_I2C_LCD_CHARACTER_DISPLAY
void IotApp::lcdClear() {
  if (lcdDriver != nullptr) {
    lcdDriver->clear();
  }
}

void IotApp::lcdClearLine(int line) {
  if (lcdDriver != nullptr) {
    lcdDriver->clearLine(line);
  }
}

void IotApp::lcdPrint(int x, int y, const char* message) {
  if (lcdDriver != nullptr) {
    lcdDriver->print(x, y, message);
  }
}

void IotApp::lcdPrintLine(int line, const char* message, bool isLoop) {
  if (lcdDriver != nullptr) {
    lcdDriver->printLine(line, message, isLoop);
  }
}

void IotApp::lcdPrint(const char* message) {
  if (lcdDriver != nullptr) {
    lcdDriver->print(message);
  }
}
#endif // CONFIG_ENABLE_I2C_LCD_CHARACTER_DISPLAY

void IotApp::suspendAllTasks(bool keepOTATasks) {
  for (auto & task : tasks) {
    if (task->started()
        && !task->isPaused()
        && (!keepOTATasks || !task->isAllowedDuringOTA())) {

      task->pause();
    }
  }
}

void IotApp::resumeAllTasks() {
  for (auto & task : tasks) {
    if (task->started()
        && task->isPaused()) {

      task->resume();
    }
  }
}

void IotApp::removeAllTasks(bool keepOTATasks) {
  for (auto & task : tasks) {
    if (task->started()
        && (!keepOTATasks || !task->isAllowedDuringOTA())) {

      task->remove();
    }
  }
}
