#pragma once

#include "include/builtin.h"
#include <WiFi.h>

#include <IPAddress.h>

#include "IotPlugin.h"
#include <Ticker.h>

class WifiDriver : public IotPlugin {
public:
  WifiDriver() : IotPlugin("WiFi Driver") { }

  static bool connected() { return WiFiClass::status() == WL_CONNECTED; }
  static std::string getIpAddress();

  bool setup() override;
  bool start() override;
  static bool startInternal();
};

extern WifiDriver Wifi;
