#pragma once

#include <Preferences.h>

#define PREF_NAMESPACE_BIRD_IOT "bird-iot"
#define PREF_BOOT_COUNT "boot_count"
#define PREF_CURRENT_REVISION "c_rev"
#define PREF_CURRENT_VERSION "c_ver"
#define PREF_CURRENT_ELF_SHA256 "elf_sha256"
#define PREF_VERSION_BOOT_COUNT "v_boot"
#define PREF_BOOTS_SINCE_WIFI_CONNECTION "no_wifi"
#define PREF_BOOTS_SINCE_MQTT_CONNECTION "no_mqtt"
#define PREF_OTA_IN_FLIGHT "ota_if"
#define PREF_TFT_ROTATION "tft_rot"
#define PREF_TFT_DISPLAY_ON "tft_on"
#define PREF_RESET_REASON "rst"

class PreferencesHelper {
private:
  // batchLocked disables the open and close functions to allow re-use of the session
  bool batchLocked = false;
public:
  Preferences prefs;

  bool open();
  bool openReadOnly();
  void close();

  void acquireBatchLock() { open(); batchLocked = true; }
  void releaseBatchLock() { batchLocked = false; close(); }

  void resetCounter(const char* key);
  uint32_t getAndDecrement(const char* key);
  uint32_t decrementAndGet(const char *key);
  uint32_t getAndIncrement(const char* key);
  uint32_t incrementAndGet(const char *key);
  // returns version boots
  uint32_t versionChecker();

  void setResetReason(uint8_t code);
  uint8_t getAndClearResetReason();

  uint32_t getCounter(const char *key);
  bool getBool(const char* key, bool defaultVal = false);
  void setBool(const char* key, bool value);

  uint8_t getUint8(const char* key, uint8_t defaultVal);
  void setUint8(const char* key, uint8_t value);
};

extern PreferencesHelper Prefs;
