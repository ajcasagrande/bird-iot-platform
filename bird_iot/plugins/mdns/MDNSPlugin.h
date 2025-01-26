#pragma once
#include "sdkconfig.h"

#if CONFIG_ENABLE_MDNS_PLUGIN

#include "include/common.h"

class MDNSPlugin : public IotPlugin {
public:
  MDNSPlugin() : IotPlugin("MDNS Plugin") { }

  bool setup() override;
  void destroy();

  void onWifiConnected() override;

private:
  bool registered = false;
  bool initialized = false;
};

extern MDNSPlugin mDNS;

#endif // CONFIG_ENABLE_MDNS_PLUGIN
