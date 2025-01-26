#include "prefs.h"

#include <esp_ota_ops.h>
#include "DevicePlugin.h"
#include "include/logging.h"
#include "include/version.h"

#define WITH_PREFS(code) open(); code; close()

static const char* TAG = "prefs";

PreferencesHelper Prefs;

bool PreferencesHelper::open() {
  if (batchLocked) {
    return true;
  }
  return prefs.begin(PREF_NAMESPACE_BIRD_IOT, false);
}

bool PreferencesHelper::openReadOnly() {
  if (batchLocked) {
    return true;
  }
  return prefs.begin(PREF_NAMESPACE_BIRD_IOT, true);
}

void PreferencesHelper::close() {
  if (!batchLocked) {
    prefs.end();
  }
}

uint32_t PreferencesHelper::getAndIncrement(const char *key) {
  open();

  uint32_t val = prefs.getUInt(key, 0);
  prefs.putUInt(key, val + 1);

  close();
  return val;
}

uint32_t PreferencesHelper::incrementAndGet(const char *key) {
  open();

  uint32_t val = prefs.getUInt(key, 0);
  val++;
  prefs.putUInt(key, val);

  close();
  return val;
}

uint32_t PreferencesHelper::getAndDecrement(const char *key) {
  open();

  uint32_t val = prefs.getUInt(key, 0);
  if (val > 0) {
    prefs.putUInt(key, val - 1);
  }

  close();
  return val;
}

uint32_t PreferencesHelper::decrementAndGet(const char *key) {
  open();

  uint32_t val = prefs.getUInt(key, 0);
  if (val > 0) {
    val--;
    prefs.putUInt(key, val);
  }

  close();
  return val;
}

uint32_t PreferencesHelper::versionChecker() {
  acquireBatchLock();

  uint32_t versionBootCount;

  char sha256[65];
  esp_ota_get_app_elf_sha256(sha256, sizeof(sha256));

  String currentSha256 = prefs.getString(PREF_CURRENT_ELF_SHA256, "");
  String currentVersion = prefs.getString(PREF_CURRENT_VERSION, "");
  String currentRevision = prefs.getString(PREF_CURRENT_REVISION, "");

  if (currentSha256 != sha256) {
    if (currentSha256 != "") {
      LOGI(TAG, "Sketch SHA-256 changed from " << currentSha256 << " to " << sha256);
      LOGI(TAG, "Software Version upgraded from " << currentVersion << " to " SOFTWARE_VERSION);
      LOGI(TAG, "Software Revision upgraded from " << currentRevision << " to " SOFTWARE_REVISION);
    }
    prefs.putString(PREF_CURRENT_ELF_SHA256, sha256);
    prefs.putString(PREF_CURRENT_VERSION, SOFTWARE_VERSION);
    prefs.putString(PREF_CURRENT_REVISION, SOFTWARE_REVISION);
    versionBootCount = 1;
  } else {
    versionBootCount = prefs.getUInt(PREF_VERSION_BOOT_COUNT, 0) + 1;
  }

  prefs.putUInt(PREF_VERSION_BOOT_COUNT, versionBootCount);

  incrementAndGet(PREF_BOOTS_SINCE_WIFI_CONNECTION);
  incrementAndGet(PREF_BOOTS_SINCE_MQTT_CONNECTION);

  releaseBatchLock();
  return versionBootCount;
}

void PreferencesHelper::resetCounter(const char *key) {
  WITH_PREFS(prefs.putUInt(key, 0));
}

uint32_t PreferencesHelper::getCounter(const char *key) {
  WITH_PREFS(uint32_t val = prefs.getUInt(key, 0));
  return val;
}

bool PreferencesHelper::getBool(const char *key, bool defaultVal) {
  WITH_PREFS(bool val = prefs.getBool(key, defaultVal));
  return val;
}

void PreferencesHelper::setBool(const char *key, bool value) {
  WITH_PREFS(prefs.putBool(key, value));
}

uint8_t PreferencesHelper::getUint8(const char *key, uint8_t defaultVal) {
  WITH_PREFS(uint8_t val = prefs.getUShort(key, defaultVal));
  return val;
}

void PreferencesHelper::setUint8(const char *key, uint8_t value) {
  WITH_PREFS(prefs.putUShort(key, value));
}

uint8_t PreferencesHelper::getAndClearResetReason() {
  acquireBatchLock();
  auto reason = prefs.getUShort(PREF_RESET_REASON, (uint8_t)RST_UNKNOWN);
  prefs.putUShort(PREF_RESET_REASON, (uint8_t)RST_UNKNOWN);
  releaseBatchLock();
  return reason;
}

void PreferencesHelper::setResetReason(uint8_t code) {
  setUint8(PREF_RESET_REASON, code);
}
