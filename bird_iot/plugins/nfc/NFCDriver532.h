#pragma once
#include "sdkconfig.h"

#if CONFIG_ENABLE_NFC_DRIVER_532

#include "common.h"

#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>

class NFCDriver532 : public IotPlugin {
public:
  NFCDriver532();

  PN532_I2C *pn532i2c;
  PN532 *nfc;

  void execute();

  Task<NFCDriver532> *task;

  bool setup() override;
  bool start() override;
//  void onWifiConnected() override;
//  void onWifiDisconnected() override;
//  void onMqttConnected() override;
//  void onMqttDisconnected() override;
//  bool handleMqttMessage(const char *topic, int id, const char *cmd, const JsonDocument& json) override;
//  bool handleCommand(const std::string& cmd) override;
#if CONFIG_ENABLE_I2C_OLED_DISPLAY_PLUGIN
//  void addFramesAndOverlays() override;
#endif
};

#endif // CONFIG_ENABLE_NFC_DRIVER_532
