#pragma once

#include "sdkconfig.h"

#if CONFIG_ENABLE_BLE_KEYBOARD_PLUGIN

#include "common.h"
#include <BLEServer.h>
#include <BLEHIDDevice.h>
#include <BLECharacteristic.h>

class BLEKeyboardPlugin : public IotPlugin, public BLEServerCallbacks, public ExclusiveLockable {
public:
  BLEKeyboardPlugin();

  bool bleConnected = false;

  BLEServer *server;
  BLEHIDDevice* hid;
  BLEAdvertising* advertising;
  BLECharacteristic* input;
  BLECharacteristic* inputMedia;

  bool setupBLE();

  bool sendKey(uint16_t key, uint8_t modifiers=0, bool release=true, int duration=0);
  bool sendMediaKey(uint16_t key, bool release=true, int duration=0);
  bool releaseKeys(uint8_t modifiers=0);
  bool sendSequence(JsonArrayConst& seq, int delay=0);

  void destroy();

  bool setup() override;
//  bool start() override;
  void execute();

  void onConnect(BLEServer*) override;
  void onDisconnect(BLEServer*) override;
//  void onWifiConnected() override;
//  void onWifiDisconnected() override;
   void onMqttConnected() override;
//  void onMqttDisconnected() override;
   bool handleMqttMessage(const char *topic, int id, const char *cmd, const JsonDocument& json) override;
//  bool handleCommand(const std::string& cmd) override;
#if ENABLE_I2C_OLED_DISPLAY_PLUGIN
//  void addFramesAndOverlays() override;
#endif

private:
  Task<BLEKeyboardPlugin> *task;
};

extern BLEKeyboardPlugin BLEKeyboard;

#endif // CONFIG_ENABLE_BLE_KEYBOARD_PLUGIN
