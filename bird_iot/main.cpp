#include "sdkconfig.h"
#include "include/common.h"
#include "Runtime.h"
#include "SpektrumDeviceMode.h"
#include "nvs_flash.h"
#include <esp_bt.h>
#include "rtos/xprintf.h"

#if CONFIG_ENABLE_CONSOLE_PLUGIN
#include "ConsoleHelper.h"
#endif

static const char* TAG = "main";

static void initNVS() {
  esp_err_t err = nvs_flash_init();
  if (err == ESP_ERR_NVS_NO_FREE_PAGES) {
    const esp_partition_t *partition = esp_partition_find_first(ESP_PARTITION_TYPE_DATA, ESP_PARTITION_SUBTYPE_DATA_NVS, nullptr);
    if (partition != nullptr) {
      err = esp_partition_erase_range(partition, 0, partition->size);
      if (!err) {
        err = nvs_flash_init();
      } else {
        LOGE(TAG, "Failed to format the broken NVS partition!");
      }
    }
  }
  if (err) {
    LOGE(TAG, "Failed to initialize NVS! Error: " << err);
  }
}

static void versionCheck() {
  uint32_t bootCount = Prefs.incrementAndGet(PREF_BOOT_COUNT);
  uint32_t versionBootCount = Prefs.versionChecker();
  LOGI(TAG, "All-Time Boot Count: " << bootCount);
  LOGI(TAG, "This Version Boot Count: " << versionBootCount);

  uint32_t failedBoots = min(versionBootCount, Prefs.getCounter(PREF_BOOTS_SINCE_WIFI_CONNECTION));
  if (failedBoots >= CONFIG_SAFE_MODE_WIFI_ONLY_THRESHOLD && CONFIG_SAFE_MODE_WIFI_ONLY_THRESHOLD > 0) {
    SafeMode.activate();
  } else if (failedBoots >= CONFIG_SAFE_MODE_MQTT_THRESHOLD && CONFIG_SAFE_MODE_MQTT_THRESHOLD > 0) {
    SafeMode.withMqtt()->activate();
  }
}

static void appTask(void* _) {
#ifdef F_CPU
  setCpuFrequencyMhz(F_CPU/1000000);
#endif

#if CONFIG_ENABLE_CONSOLE_PLUGIN
  ESP_ERROR_CHECK(initialize_uart());
  ESP_ERROR_CHECK(initialize_filesystem());
#endif

  Serial.begin(CONFIG_CONSOLE_UART_BAUDRATE);
  // make sure we start on a fresh line
  Serial.println();

#if CONFIG_ENABLE_I2C_SLAVE
  SpektrumDeviceMode.activate();
#else
  initNVS();
  versionCheck();

#if CONFIG_SPIRAM_SUPPORT
  psramInit();
#endif

#if CONFIG_ENABLE_BLE_BEACON || CONFIG_ENABLE_BLE_KEYBOARD_PLUGIN
  esp_bt_controller_mem_release(ESP_BT_MODE_CLASSIC_BT);
#elif !CONFIG_ENABLE_NIMBLE_PLUGIN
  esp_bt_controller_mem_release(ESP_BT_MODE_BTDM);
#endif

  // for now just call these methods to get their memory usage out of the way
  deviceId();
  millis64();
  readVcc();

  if (!SafeMode.isActive()) {
    Runtime.activate();
  }
#endif

  verifyHeap();
  // once setup we do not need this task anymore
  vTaskDelete(nullptr);
}

extern "C" void app_main() {
  esp_log_set_vprintf(xvprintf);
  xTaskCreatePinnedToCore(&appTask, "App Main", _6k, nullptr, MEDIUM_PRIORITY, nullptr, CORE_1);
}
