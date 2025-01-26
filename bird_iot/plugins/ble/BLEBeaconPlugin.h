#pragma once
#include "sdkconfig.h"

#if CONFIG_ENABLE_BLE_BEACON
#include <esp_gap_ble_api.h>
#include "include/common.h"

typedef struct {
  uint8_t flags[3];
  uint8_t length;
  uint8_t type;
  uint16_t company_id;
  uint16_t beacon_type;
} __attribute__((packed)) esp_ble_ibeacon_head_t;

typedef struct {
  uint8_t proximity_uuid[16];
  uint16_t major;
  uint16_t minor;
  uint8_t measured_power;
} __attribute__((packed)) esp_ble_ibeacon_vendor_t;

typedef struct {
  esp_ble_ibeacon_head_t ibeacon_head;
  esp_ble_ibeacon_vendor_t ibeacon_vendor;
} __attribute__((packed)) esp_ble_ibeacon_t;


class BLEBeaconPlugin : public IotPlugin {
private:

public:
  explicit BLEBeaconPlugin(const std::array<uint8_t, 16> &uuid) : IotPlugin("BLEBeacon Plugin"), uuid_(uuid) { }

  bool setup() override;
//  bool start() override;
  void set_major(uint16_t major) { this->major_ = major; }
  void set_minor(uint16_t minor) { this->minor_ = minor; }

  void destroy();

protected:
  static void gap_event_handler(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param);
  static bool ble_setup();

  std::array<uint8_t, 16> uuid_;
  uint16_t major_{};
  uint16_t minor_{};
};

extern BLEBeaconPlugin Beacon;
#endif // CONFIG_ENABLE_BLE_BEACON
