#include "SPIFFSPlugin.h"

#if CONFIG_ENABLE_SPIFFS_PLUGIN

#include <esp_spiffs.h>
#include <SPIFFS.h>

SPIFFSPlugin Spiffs;

static const char* TAG = "SPIFFS";

bool SPIFFSPlugin::setup() {
  if (!SPIFFS.begin(true)) {
    return false;
  }

  LOGI(TAG, "SPIFFS started");

  size_t total, used;
  if (esp_spiffs_info(nullptr, &total, &used) != ESP_OK){
    return false;
  }

  LOGI(TAG, "SPIFFS total size: " << formatBytes(total) << ", used size: " << formatBytes(used));

  return true;
}

#endif // CONFIG_ENABLE_SPIFFS_PLUGIN
