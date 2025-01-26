#include "BLEBeaconPlugin.h"
#if CONFIG_ENABLE_BLE_BEACON

#include <nvs_flash.h>
#include <esp_bt_main.h>
#include <esp_bt.h>
#include <esp_gap_ble_api.h>

BLEBeaconPlugin Beacon({0xFF});

static const char *TAG = "BLE";

static esp_ble_adv_params_t ble_adv_params = {
    .adv_int_min = 0x20,
    .adv_int_max = 0x40,
    .adv_type = ADV_TYPE_NONCONN_IND,
    .own_addr_type = BLE_ADDR_TYPE_PUBLIC,
    .peer_addr = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    .peer_addr_type = BLE_ADDR_TYPE_PUBLIC,
    .channel_map = ADV_CHNL_ALL,
    .adv_filter_policy = ADV_FILTER_ALLOW_SCAN_ANY_CON_ANY,
};

#define ENDIAN_CHANGE_U16(x) ((((x) &0xFF00) >> 8) + (((x) &0xFF) << 8))

static esp_ble_ibeacon_head_t ibeacon_common_head = {
    .flags = {0x02, 0x01, 0x06}, .length = 0x1A, .type = 0xFF, .company_id = 0x004C, .beacon_type = 0x1502};

bool BLEBeaconPlugin::setup() {
  LOGI(TAG, "Setting up ESP32 BLE beacon...");
  set_major((uint16_t)esp_random());
  set_minor((uint16_t)esp_random());
  return ble_setup();
}

bool BLEBeaconPlugin::ble_setup() {
  // Initialize non-volatile storage for the bluetooth controller
  esp_err_t err = nvs_flash_init();
  if (err != ESP_OK) {
    LOGE(TAG, "nvs_flash_init failed: " << err);
    return false;
  }

  if (!btStart()) {
    LOGE(TAG, "btStart failed");
    return false;
  }

  err = esp_bluedroid_init();
  if (err != ESP_OK) {
    LOGE(TAG, "esp_bluedroid_init failed: " << err);
    return false;
  }
  err = esp_bluedroid_enable();
  if (err != ESP_OK) {
    LOGE(TAG, "esp_bluedroid_enable failed: " << err);
    return false;
  }

  err = esp_ble_gap_register_callback(BLEBeaconPlugin::gap_event_handler);
  if (err != ESP_OK) {
    LOGE(TAG, "esp_ble_gap_register_callback failed: " << err);
    return false;
  }

  esp_ble_ibeacon_t ibeacon_adv_data;
  memcpy(&ibeacon_adv_data.ibeacon_head, &ibeacon_common_head, sizeof(esp_ble_ibeacon_head_t));
  memcpy(&ibeacon_adv_data.ibeacon_vendor.proximity_uuid, Beacon.uuid_.data(),
         sizeof(ibeacon_adv_data.ibeacon_vendor.proximity_uuid));
  ibeacon_adv_data.ibeacon_vendor.minor = ENDIAN_CHANGE_U16(Beacon.minor_);
  ibeacon_adv_data.ibeacon_vendor.major = ENDIAN_CHANGE_U16(Beacon.major_);
  ibeacon_adv_data.ibeacon_vendor.measured_power = 0xC5;

  LOGI(TAG, "Beacon major: " << Beacon.major_);
  LOGI(TAG, "Beacon minor: " << Beacon.minor_);

  esp_ble_gap_config_adv_data_raw((uint8_t *) &ibeacon_adv_data, sizeof(ibeacon_adv_data));

  return true;
}

void BLEBeaconPlugin::destroy() {
  esp_bluedroid_disable();
  esp_bluedroid_deinit();
  esp_bt_controller_mem_release(ESP_BT_MODE_BTDM);
}

void BLEBeaconPlugin::gap_event_handler(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param) {
  esp_err_t err;
  switch (event) {
    case ESP_GAP_BLE_ADV_DATA_RAW_SET_COMPLETE_EVT: {
      err = esp_ble_gap_start_advertising(&ble_adv_params);
      if (err != ESP_OK) {
        LOGE(TAG, "esp_ble_gap_start_advertising failed: " << err);
      }
      break;
    }
    case ESP_GAP_BLE_ADV_START_COMPLETE_EVT: {
      err = param->adv_start_cmpl.status;
      if (err != ESP_BT_STATUS_SUCCESS) {
        LOGE(TAG, "BLE adv start failed:" << esp_err_to_name(err));
      }
      break;
    }
    case ESP_GAP_BLE_ADV_STOP_COMPLETE_EVT: {
      err = param->adv_start_cmpl.status;
      if (err != ESP_BT_STATUS_SUCCESS) {
        LOGE(TAG, "BLE adv stop failed: " << esp_err_to_name(err));
      } else {
        LOGD(TAG, "BLE stopped advertising successfully");
      }
      break;
    }
    default:
      break;
  }
}

#endif // CONFIG_ENABLE_BLE_BEACON
