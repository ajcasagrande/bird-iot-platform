#include "MDNSPlugin.h"
#if CONFIG_ENABLE_MDNS_PLUGIN

#include <mdns.h>
#include "include/version.h"

MDNSPlugin mDNS;

static const char* TAG = "MDNS";

static void _on_sys_event(system_event_t *event) {
  mdns_handle_system_event(nullptr, event);
}

bool MDNSPlugin::setup() {
  WiFi.onEvent(_on_sys_event);
  return true;
}

void MDNSPlugin::destroy() {
  if (!initialized) {
    return;
  }
  initialized = false;
  registered = false;
  mdns_service_remove_all();
  mdns_free();
}

void MDNSPlugin::onWifiConnected() {
  if (!initialized) {
    LOGD(TAG, "init mdns");
    // NOTE: mdns_init will fail if wifi is not connected!
    esp_err_t err = mdns_init();
    if (err != ESP_OK) {
      LOGE(TAG, "unable to initialize mdns: " << esp_err_to_name(err));
      return;
    }

    LOGD(TAG, "set mdns hostname");
    mdns_hostname_set(deviceId());

    initialized = (err == ESP_OK);
  }

  if (initialized && !registered) {
    LOGD(TAG, "registering mdns service");

    int txtSize = 4;
    mdns_txt_item_t txt[txtSize];
    txt[0] = {(char *) "version", (char *) SOFTWARE_VERSION};
    txt[1] = {(char *) "revision", (char *) SOFTWARE_REVISION};
    txt[2] = {(char *) "env", (char *) CONFIG_BIRD_IOT_ENV};
    txt[3] = {(char *) "update_channel", (char *) (App.profile.updateChannel == SOFTWARE_CHANNEL_STABLE ? "stable" : "dev")};

    esp_err_t err = mdns_service_add(deviceId(), CONFIG_MDNS_SERVICE_TYPE, "_tcp", CONFIG_WEBSOCKET_SERVER_PORT, txt, txtSize);
    if (err != ESP_OK) {
      LOGE(TAG, "unable to register mdns service: " << esp_err_to_name(err));
    } else {
      LOGD(TAG, "successfully registered mdns service");
    }
    registered = (err == ESP_OK);
  }
}

#endif // CONFIG_ENABLE_MDNS_PLUGIN
