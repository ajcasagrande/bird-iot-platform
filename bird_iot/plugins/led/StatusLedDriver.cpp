#include "StatusLedDriver.h"

#if CONFIG_ENABLE_STATUS_LED_DRIVER

#include "LED.h"

StatusLedDriver::StatusLedDriver() : IotPlugin("Status Led Driver") {
  // todo
}

bool StatusLedDriver::setup() {
  StatusLed.setup();
  NetworkLed.setup();
  return true;
}

#endif // CONFIG_ENABLE_STATUS_LED_DRIVER
