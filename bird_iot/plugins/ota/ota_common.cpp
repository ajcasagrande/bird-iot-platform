#include "ota_common.h"
#include "prefs.h"
#include "SecureOTAPlugin.h"

bool otaInProgress() {
  return false
#if CONFIG_ENABLE_SECURE_OTA_PLUGIN
     || SecureOTA.isInProgress()
#endif
  ;
}

void setOtaInFlight(bool value) {
  Prefs.setBool(PREF_OTA_IN_FLIGHT, value);
}

bool wasOtaInFlight() {
  return Prefs.getBool(PREF_OTA_IN_FLIGHT, false);
}

