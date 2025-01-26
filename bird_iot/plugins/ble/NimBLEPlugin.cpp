#include "NimBLEPlugin.h"
#if CONFIG_ENABLE_NIMBLE_PLUGIN

#include "esp_bt.h"
#include "host/ble_hs.h"
#include "nimble/nimble_port.h"
#include "esp_nimble_hci.h"
#include "include/rtos.h"

static const char* TAG = "NimBLE";

NimBLEPlugin NimBLE;

//static void ble_app_set_addr() {
//    ble_addr_t addr;
//    int rc;
//
//    if ((rc = ble_hs_id_gen_rnd(1, &addr)) != ESP_OK) {
//      LOGE(TAG, "ble_hs_id_gen_rnd returned: " << rc);
//      return;
//    }
//
//    if ((rc = ble_hs_id_set_rnd(addr.val)) != ESP_OK) {
//      LOGE(TAG, "ble_hs_id_set_rnd returned: " << rc);
//      return;
//    }
//}

static void ble_app_advertise() {
  struct ble_gap_adv_params adv_params;
  uint8_t uuid128[16];
  int rc;

  memset(uuid128, 0, sizeof(uuid128));
  esp_efuse_mac_get_default(uuid128);

  if ((rc = ble_ibeacon_set_adv_data(uuid128, Prefs.getCounter(PREF_BOOT_COUNT), Prefs.getCounter(PREF_VERSION_BOOT_COUNT), -70)) != ESP_OK) {
    LOGE(TAG, "ble_ibeacon_set_adv_data returned: " << rc);
    return;
  }

  // Begin advertising.
  memset(&adv_params, 0, sizeof(adv_params));
  if ((rc = ble_gap_adv_start(BLE_OWN_ADDR_PUBLIC, nullptr, BLE_HS_FOREVER, &adv_params, nullptr, nullptr)) != ESP_OK) {
    LOGE(TAG, "ble_gap_adv_start returned: " << rc);
    return;
  }
}

static void ble_app_on_sync() {
//  LOGI(TAG, "BLE set address");
//  ble_app_set_addr();

  // Advertise indefinitely.
  LOGI(TAG, "BLE advertise");
  ble_app_advertise();
}

void _nimble_task(NimBLEPlugin *plugin) {
  LOGI(TAG, "BLE Host Task Started");

  if (esp_vhci_host_check_send_available()) {
    // This function will return only when nimble_port_stop() is executed
    nimble_port_run();
  }
}

NimBLEPlugin::NimBLEPlugin() : IotPlugin("NimBLE Plugin") {
  task = new Task<NimBLEPlugin>("NimBLE", this, _nimble_task);
}

bool NimBLEPlugin::setup() {
  int ret = esp_nimble_hci_and_controller_init();
  if (ret != ESP_OK) {
    LOGE(TAG, "esp_nimble_hci_and_controller_init() failed with error: " << ret);
    return false;
  }

  nimble_port_init();

  //Initialize the NimBLE Host configuration
  memset(&ble_hs_cfg, 0, sizeof(ble_hs_cfg));
  ble_hs_cfg.sync_cb = ble_app_on_sync;

  return task->configure(2500, CONFIG_BT_NIMBLE_TASK_STACK_SIZE, MEDIUM_PRIORITY);
}

bool NimBLEPlugin::start() {
  return task->start();
}

void NimBLEPlugin::destroy() {
  if (task->started()) {
    nimble_port_stop();
  }
  task->remove();
}

//  void NimBLEPlugin::onWifiConnected() { }
//  void NimBLEPlugin::onWifiDisconnected() { }
//  void NimBLEPlugin::onMqttConnected() { }
//  void NimBLEPlugin::onMqttDisconnected() { }
//  bool NimBLEPlugin::handleMqttMessage(const char *topic, int id, const char *cmd, const JsonDocument& json) {
//   return false; // false means not handled 
// }
//  bool NimBLEPlugin::handleCommand(const std::string& cmd) {
//   return false; // false means not handled 
// }
#if CONFIG_ENABLE_I2C_OLED_DISPLAY_PLUGIN
//  void NimBLEPlugin::addFramesAndOverlays() { }
#endif

#endif // CONFIG_ENABLE_NIMBLE_PLUGIN
