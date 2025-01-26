#include "WifiDriver.h"

#include <esp_wifi.h>
#include "include/common.h"
#include "include/private.h"

WifiDriver Wifi;

static const char* TAG = "Wifi";

std::string WifiDriver::getIpAddress() {
  static const char* _digits = "0123456789abcdef";

  tcpip_adapter_ip_info_t _ip;
  tcpip_adapter_get_ip_info(TCPIP_ADAPTER_IF_STA, &_ip);

  char ip[16];
  char *ptr = ip;
  uint8_t val, rem, i, j;
  bool set = false;
  for (i = 0; i < 4; i++) {
    val = (_ip.ip.addr >> (8*i)) & 0xff;
    if (val == 0) {
      *ptr++ = '0';
    } else {
      for (j = 100; j >= 1; j /= 10) {
        rem = val % j;
        if (set || rem != val) {
          set = true;
          *ptr++ = _digits[val / j];
          val = rem;
        }
      }
    }

    *ptr++ = '.';
    set=false;
  }
  // override the last period
  *(ptr-1) = '\0';

  return std::string(ip);
}

static void _onWifiConnect(system_event_id_t event) {
  LOGI(TAG, "wifi connection established");
  Prefs.resetCounter(PREF_BOOTS_SINCE_WIFI_CONNECTION);

  // NOTE: I removed the check for SafeMode because that was actually
  //       preventing some plugins like MQTT from even working!

  if (!App.isSetupComplete()) {
    LOGW(TAG, "waiting for setup of app to complete before processing wifi callbacks!");
    // wait for setup to be complete
    while (!App.isSetupComplete()) {
      taskDELAY(10);
    }
    LOGI(TAG, "resume processing wifi callbacks");
  }

  for (auto & plugin : App.getPlugins()) {
    plugin->onWifiConnected();
  }
}

static void _onWifiDisconnect(system_event_id_t event) {
  LOGW(TAG, "wifi connection lost");

  if (!App.isSetupComplete()) {
    LOGW(TAG, "setup of app is not yet complete, skipping disconnection event");
  }

  for (auto & plugin : App.getPlugins()) {
    plugin->onWifiDisconnected();
  }
}

bool WifiDriver::setup() {
  WiFi.onEvent(&_onWifiConnect, SYSTEM_EVENT_STA_GOT_IP);
  WiFi.onEvent(&_onWifiDisconnect, SYSTEM_EVENT_STA_DISCONNECTED);
  return true;
}

bool WifiDriver::start() {
  return startInternal();
}

bool WifiDriver::startInternal() {
  WiFiClass::mode(WIFI_STA);
#if !CONFIG_ENABLE_BLE_BEACON && !CONFIG_ENABLE_BLE_KEYBOARD_PLUGIN && !CONFIG_ENABLE_NIMBLE_PLUGIN
  esp_wifi_set_ps(WIFI_PS_NONE);
#endif
  WiFi.softAPdisconnect(true);

#if defined(USE_STATIC_IP)
  // config static IP based on the efuse mac
  int lastDigit = 200 + (int)(ESP.getEfuseMac() % 54);
  IPAddress ip(10, 0, 0, lastDigit);
  IPAddress gateway(10, 0, 0, 1);
  IPAddress subnet(255, 255, 255, 0);
  WiFi.config(ip, gateway, subnet);
#endif

  WiFi.setHostname(deviceId());

//  if (App.profile.wifiScanIntervalSeconds > 0) {
//    scanTicker = new Ticker();
//    scanTicker->attach_scheduled(App.profile.wifiScanIntervalSeconds, scanAndPublish);
//  }

  LOGI(TAG, "Connecting to " << WIFI_SSID << "...");
  LOGI(TAG, "WiFi.begin()");
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  return true;
}
