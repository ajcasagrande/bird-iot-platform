#pragma once

#include "sdkconfig.h"

#if CONFIG_ENABLE_STATUS_LED_DRIVER

#include "include/common.h"

class StatusLedDriver : public IotPlugin {
public:
  StatusLedDriver();
  // IotPlugin implementation
  bool setup() override;
//  bool start() override;
};

#endif // CONFIG_ENABLE_STATUS_LED_DRIVER
