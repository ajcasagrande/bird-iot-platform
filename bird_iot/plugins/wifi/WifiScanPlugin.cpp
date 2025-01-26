#include "WifiScanPlugin.h"
#if CONFIG_ENABLE_WIFI_SCAN_PLUGIN

#include <esp_wifi.h>

const char* TAG = "wifi scan";

WifiScanPlugin WifiScanner;

void WifiScanPlugin::onScanComplete() {
  uint16_t scanCount;
  esp_wifi_scan_get_ap_num(&scanCount);
  LOGI(TAG, "scan found " << scanCount << " networks");

  if (scanCount > 0) {
    DynamicJsonDocument json(JSON_ARRAY_SIZE(scanCount) + JSON_OBJECT_SIZE(1) + (JSON_OBJECT_SIZE(4) * scanCount));
    JsonArray networks = json.createNestedArray("networks");

    wifi_ap_record_t *ap;
    for (uint16_t i = 0; i < scanCount; i++) {
      ap = reinterpret_cast<wifi_ap_record_t *>(_scanResult) + i;

      char mac[18];
      xsnprintf(mac, 18, "%02x:%02x:%02x:%02x:%02x:%02x",
                ap->bssid[0], ap->bssid[1], ap->bssid[2],
                ap->bssid[3], ap->bssid[4], ap->bssid[5]);
      String macStr = String(mac);
      
      LOGD(TAG,  "ssid: " << (ap->ssid[0] == '\0' ? "*" : (const char *) ap->ssid) 
            << ", rssi: " << ap->rssi
            << ", channel: " << ap->primary
            << ", auth: " << authModeStr(ap->authmode)
            << ", mac: " << macStr
            << ", width: " << channelWidthStr(ap->second)
            << ", wps: " << ap->wps);

      JsonObject network = networks.createNestedObject();
      network["ssid"] = ap->ssid[0] == '\0' ? "*" : (const char *) ap->ssid;
      network["rssi"] = ap->rssi;
      network["chan"] = ap->primary;
      network["auth"] = authModeStr(ap->authmode);
      network["mac"] = macStr;
      network["width"] = channelWidthStr(ap->second);
      network["wps"] = ap->wps;
  //    network["pairwise_cipher"] = cipherTypeStr(ap->pairwise_cipher);
  //    network["group_cipher"] = cipherTypeStr(ap->group_cipher);
    }

    Mqtt.publish(Mqtt.topics.wifi_scan, json);
  }
  scanDelete();
}

void onWiFiEvent(WiFiEvent_t event) {
  if (event == SYSTEM_EVENT_SCAN_DONE) {
    LOGI(TAG, "wifi scan completed");
    WifiScanner.onScanComplete();
  }
}

static void _execute(WifiScanPlugin *plugin) {
  plugin->execute();
}

WifiScanPlugin::WifiScanPlugin() : IotPlugin("WifiScan Plugin") {
  scanTask = new Task<WifiScanPlugin>("Wifi Scan", this, _execute);
  WiFi.onEvent(onWiFiEvent, WiFiEvent_t::SYSTEM_EVENT_SCAN_DONE);
}

bool WifiScanPlugin::setup() {
  return scanTask->configure(App.profile.wifiScanInterval, _4k, MEDIUM_HIGH_PRIORITY, CORE_0);
}

bool WifiScanPlugin::start() {
  return scanTask->start();
}

void WifiScanPlugin::scanChannel(uint8_t channel, bool block) {
  wifi_scan_config_t config{};
  memset(&config, 0, sizeof(config));
  config.show_hidden = true;
  config.channel = channel;
  config.scan_type = WIFI_SCAN_TYPE_PASSIVE;
  config.scan_time = wifi_scan_time_t{.passive = App.profile.wifiScanMillisPerChannel};
  esp_wifi_scan_start(&config, block);
}

void WifiScanPlugin::scanAll(uint32_t channelDelay) {
  for (int i=1; i <= 11; ++i) {
    LOGI(TAG, "scanning for wifi networks on channel " << i << "...");
    scanChannel(i, true);
    taskDELAY(channelDelay);
  }
}

void WifiScanPlugin::execute() {
  scanAll(App.profile.wifiScanChannelDelay);
}

#endif // CONFIG_ENABLE_WIFI_SCAN_PLUGIN
