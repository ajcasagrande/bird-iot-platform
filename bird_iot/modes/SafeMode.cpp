#include "SafeMode.h"

#include "sdkconfig.h"
#include "include/builtin.h"
#include "include/logging.h"
#include "IotApp.h"
#include "include/plugins_inc.h"
#include "include/rtos.h"
#include "ota_common.h"

static const char* TAG = "SafeMode";

SafeModeClass SafeMode;

void _alertMessage() {
  if (otaInProgress()) {
    return;
  }
  LOGW(TAG, "Warning: safe mode is active!");
}

bool SafeModeClass::activate() {
  LOGW(TAG, "initializing safe mode");
  active = true;

  disableBrownoutDetector();

  taskDELAY(1000);

  // periodically remind that safe mode is active
  ticker.attach(CONFIG_SAFE_MODE_ALERT_SECONDS, &_alertMessage);

  App.registerPlugin(&Wifi);
  taskDELAY(100);

#if CONFIG_ENABLE_SECURE_OTA_PLUGIN
  App.registerPlugin(&SecureOTA);
  taskDELAY(100);
  App.registerPlugin(&Mqtt);
  taskDELAY(100);
#else
  if (enableMqtt) {
    App.registerPlugin(&Mqtt);
    taskDELAY(100);
  }
#endif

#if CONFIG_ENABLE_HEARTBEAT_TASK
  App.registerPlugin(&Heartbeat);
#endif

  bool result = App.setupPlugins();
  result = App.startPlugins() && result;

  LOGW(TAG, "safe mode initialized");
  taskDELAY(5000);
  LOGW(TAG, "re-enabling brownout detector");
  enableBrownoutDetector();
  return result;
}
