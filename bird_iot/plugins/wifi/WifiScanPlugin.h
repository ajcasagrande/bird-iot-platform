#pragma once
#include "sdkconfig.h"

#if CONFIG_ENABLE_WIFI_SCAN_PLUGIN

#include "include/common.h"
#include <WiFi.h>

class WifiScanPlugin : public IotPlugin, protected WiFiScanClass {
public:
  WifiScanPlugin();

  bool setup() override;
  bool start() override;
  void execute();

  void onScanComplete();
  static void scanChannel(uint8_t channel, bool block);

  static void scanAll(uint32_t channelDelay);

private:
  Task<WifiScanPlugin> *scanTask;

};

extern WifiScanPlugin WifiScanner;

#endif // CONFIG_ENABLE_WIFI_SCAN_PLUGIN
