#pragma once
#include "sdkconfig.h"

#if CONFIG_ENABLE_SPIFFS_PLUGIN
#include "include/common.h"

class SPIFFSPlugin : public IotPlugin {
public:
  SPIFFSPlugin() : IotPlugin("SPIFFS Plugin") { }
  bool setup() override;
//  bool start() override;
};

extern SPIFFSPlugin Spiffs;

#endif // CONFIG_ENABLE_SPIFFS_PLUGIN
