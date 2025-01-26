#include "BLEKeyboardPlugin.h"
#if CONFIG_ENABLE_BLE_KEYBOARD_PLUGIN

#define MEDIA_KEY_MODIFIER 0xFF

static const char* TAG = "BLE Keyboard";

BLEKeyboardPlugin BLEKeyboard;

#include <BLEDevice.h>
#include <BLEServer.h>
#include <esp_bt_main.h>
#include "BLE2902.h"
#include "BLEHIDDevice.h"
#include "HIDTypes.h"

struct inputConsumer_t {
  uint16_t ConsumerControl;                          // Value = 0 to 572
};

struct inputKeyboard_t {
  uint8_t  Modifiers;                               // Modifiers
  uint8_t  Key;                                     // Value = 0 to 101
};

const BLEUUID UUID_2902 = BLEUUID((uint16_t)0x2902);

const uint8_t keyboardHidDescriptor[] = {
  0x05, 0x0c,                    // USAGE_PAGE (Consumer Devices)
  0x09, 0x01,                    // USAGE (Consumer Control)
  0xa1, 0x01,                    // COLLECTION (Application)
  0x85, 0x01,                    //   REPORT_ID (1)
  0x19, 0x00,                    //   USAGE_MINIMUM (Unassigned)
  0x2a, 0x3c, 0x02,              //   USAGE_MAXIMUM (AC Format)
  0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
  0x26, 0x3c, 0x02,              //   LOGICAL_MAXIMUM (572)
  0x95, 0x01,                    //   REPORT_COUNT (1)
  0x75, 0x10,                    //   REPORT_SIZE (16)
  0x81, 0x00,                    //   INPUT (Data,Var,Abs)
  0xc0,                          // END_COLLECTION
  0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
  0x09, 0x06,                    // USAGE (Keyboard)
  0xa1, 0x01,                    // COLLECTION (Application)
  0x85, 0x02,                    //   REPORT_ID (2)
  0x05, 0x07,                    //   USAGE_PAGE (Keyboard)
  0x19, 0xe0,                    //   USAGE_MINIMUM (Keyboard LeftControl)
  0x29, 0xe7,                    //   USAGE_MAXIMUM (Keyboard Right GUI)
  0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
  0x25, 0x01,                    //   LOGICAL_MAXIMUM (1)
  0x75, 0x01,                    //   REPORT_SIZE (1)
  0x95, 0x08,                    //   REPORT_COUNT (8)
  0x81, 0x02,                    //   INPUT (Data,Var,Abs)
  0x95, 0x01,                    //   REPORT_COUNT (1)
  0x75, 0x08,                    //   REPORT_SIZE (8)
  0x25, 0x65,                    //   LOGICAL_MAXIMUM (101)
  0x19, 0x00,                    //   USAGE_MINIMUM (Reserved (no event indicated))
  0x29, 0x65,                    //   USAGE_MAXIMUM (Keyboard Application)
  0x81, 0x00,                    //   INPUT (Data,Ary,Abs)
  0xc0                           // END_COLLECTION
};

static inputConsumer_t emptyConsumerReport{0};
static inputKeyboard_t emptyKeyboardReport{0, 0};

static void _execute(BLEKeyboardPlugin *plugin) {
  plugin->execute();
}

BLEKeyboardPlugin::BLEKeyboardPlugin() : IotPlugin("BLE Keyboard") {
  task = new Task<BLEKeyboardPlugin>("BLE Keyboard", this, _execute);
}

bool BLEKeyboardPlugin::setup() {
  if (!setupBLE()) {
    return false;
  }
  return task->configure(0, _6k, MEDIUM_PRIORITY) &&
         task->fireSingleShot(100);
}

void BLEKeyboardPlugin::onConnect(BLEServer* _) {
  auto desc = (BLE2902*)input->getDescriptorByUUID(UUID_2902);
  desc->setNotifications(true);

  desc = (BLE2902*)inputMedia->getDescriptorByUUID(UUID_2902);
  desc->setNotifications(true);

  bleConnected = true;
  LOGI(TAG, "Bluetooth Connected");
  Device.sendAlert(ALERT_BLE_CONNECTED);
}

void BLEKeyboardPlugin::onDisconnect(BLEServer* _) {
  bleConnected = false;
  LOGW(TAG, "BLE Disconnected");
  Device.sendAlert(ALERT_BLE_DISCONNECTED);

  auto desc = (BLE2902*)input->getDescriptorByUUID(UUID_2902);
  desc->setNotifications(false);

  desc = (BLE2902*)inputMedia->getDescriptorByUUID(UUID_2902);
  desc->setNotifications(false);
}

bool BLEKeyboardPlugin::setupBLE() {
  if (!btStart()) {
    LOGE(TAG, "btStart failed");
    Device.sendAlertWithReason(ALERT_BLE_INIT_FAILURE, "btStart failed");
    return false;
  }

  esp_err_t err = esp_bluedroid_init();
  if (err != ESP_OK) {
    LOGE(TAG, "esp_bluedroid_init failed: " << err);
    Device.sendAlertWithReason(ALERT_BLE_INIT_FAILURE, "esp_bluedroid_init failed");
    return false;
  }
  err = esp_bluedroid_enable();
  if (err != ESP_OK) {
    LOGE(TAG, "esp_bluedroid_enable failed: " << err);
    Device.sendAlertWithReason(ALERT_BLE_INIT_FAILURE, "esp_bluedroid_enable failed");
    return false;
  }

  return true;
}

void BLEKeyboardPlugin::execute() {
  BLEDevice::init(deviceId());
  server = BLEDevice::createServer();
  server->setCallbacks(this);

  uint8_t security = ESP_LE_AUTH_BOND;
  esp_err_t err = esp_ble_gap_set_security_param(ESP_BLE_SM_AUTHEN_REQ_MODE, &security, sizeof(security));
  if (err != ESP_OK) {
    Device.sendAlertWithReason(ALERT_BLE_INIT_FAILURE, "esp_ble_gap_set_security_param failed");
  }

  hid = new BLEHIDDevice(server);
  hid->reportMap((uint8_t*)keyboardHidDescriptor, sizeof(keyboardHidDescriptor));
  hid->manufacturer()->setValue("BirdIoT");
  hid->pnp(0x02, 0xe502, 0xa111, 0x0210);
  hid->hidInfo(0x00, 0x02);

  inputMedia = hid->inputReport(1); // <-- input REPORTID from report map
  input = hid->inputReport(2); // <-- input REPORTID from report map
  hid->startServices();

  advertising = server->getAdvertising();
  advertising->setAppearance(HID_KEYBOARD);
  advertising->addServiceUUID(hid->hidService()->getUUID());
  advertising->start();

  hid->setBatteryLevel(100);
}

//  void BLEKeyboardPlugin::onWifiConnected() { }
//  void BLEKeyboardPlugin::onWifiDisconnected() { }
//  void BLEKeyboardPlugin::onMqttDisconnected() { }
//  bool BLEKeyboardPlugin::handleCommand(const std::string& cmd) {
//   return false; // false means not handled
// }

void BLEKeyboardPlugin::onMqttConnected() {
  Mqtt.subscribe(Mqtt.topics.media_control.c_str());
}

bool BLEKeyboardPlugin::releaseKeys(uint8_t modifiers) {
  bool res;
  TRY_LOCK(*this,
    // Special modifier signifies it should be sent as a media key
    if (modifiers == MEDIA_KEY_MODIFIER) {
     inputMedia->setValue((uint8_t *) &emptyConsumerReport, sizeof(emptyConsumerReport));
     inputMedia->notify();
    } else {
     input->setValue((uint8_t*) &emptyKeyboardReport, sizeof(emptyKeyboardReport));
     input->notify();
    }
    res = true;
  , res = false;);
  return res;
}

bool BLEKeyboardPlugin::sendKey(uint16_t key, uint8_t modifiers, bool release, int duration) {
  // Special modifier signifies it should be sent as a media key
  if (modifiers == MEDIA_KEY_MODIFIER) {
    return sendMediaKey(key, release, duration);
  }

  LOGD(TAG, "Sending key code: " << key << ", modifiers: " << modifiers);
  inputKeyboard_t keyboard{modifiers, (uint8_t) key};
  bool res;
  TRY_LOCK(*this,
    input->setValue((uint8_t*)&keyboard, sizeof(keyboard));
    input->notify();
    if (release) {
      // for long presses
      if (duration > 0) {
        taskDELAY(duration);
      }
      input->setValue((uint8_t*) &emptyKeyboardReport, sizeof(emptyKeyboardReport));
      input->notify();
    }
    res = true;
  , res = false;);
  return res;
}

bool BLEKeyboardPlugin::sendMediaKey(uint16_t key, bool release, int duration) {
  LOGD(TAG, "Sending media key code: " << key);
  inputConsumer_t consumer{key};
  bool res;
  TRY_LOCK(*this,
    inputMedia->setValue((uint8_t*)&consumer, sizeof(consumer));
    inputMedia->notify();
    if (release) {
      // for long presses
      if (duration > 0) {
        taskDELAY(duration);
      }
      inputMedia->setValue((uint8_t*) &emptyConsumerReport, sizeof(emptyConsumerReport));
      inputMedia->notify();
    }
    res = true;
  , res = false;);
  return res;
}

bool BLEKeyboardPlugin::sendSequence(JsonArrayConst& seq, int delay) {
  size_t size = seq.size();
  if (size % 2 != 0) {
    LOGW(TAG, "key sequence needs to be an even number, but was: " << size);
    return false;
  }

  bool res = true;
  uint8_t modifiers;
  uint16_t key;
  for (int i=0; i < size && res; i += 2) {
    // alternate key then modifier
    // example sequence: [key1, mod1, key2, mod2, key3, mod3, etc.]
    key = seq[i].as<uint16_t>();
    modifiers = seq[i + 1].as<uint8_t>();
    res = sendKey(key, modifiers, true, 0);
    if (res && delay > 0) {
      // optional delay between each key press
      taskDELAY(delay);
    }
  }
  return res;
}

bool BLEKeyboardPlugin::handleMqttMessage(const char *topic, int id, const char *cmd, const JsonDocument& json) {
  if (Mqtt.topics.media_control == topic) {
    if (strcmp(cmd, "send_key") == 0 || strcmp(cmd, "key_down") == 0) {
      int duration;
      uint8_t modifiers;
      bool release = strcmp(cmd, "send_key") == 0;
      getJsonProperty(uint16_t key, "key");
      getOrDefaultJsonProperty(duration, "duration", 0);
      getOrDefaultJsonProperty(modifiers, "mod", 0);
      sendKey(key, modifiers, release, duration);

    } else if (strcmp(cmd, "key_up") == 0) {
      uint8_t modifiers;
      getOrDefaultJsonProperty(modifiers, "mod", 0);
      releaseKeys(modifiers);

    } else if (strcmp(cmd, "send_sequence") == 0) {
      int delay;
      getJsonProperty(JsonArrayConst seq, "seq");
      getOrDefaultJsonProperty(delay, "delay", 0);
      sendSequence(seq, delay);

    } else if (strcmp(cmd, "status") == 0) {
      Mqtt.respondWith(id, "result", json_lambda(1,,js["connected"] = BLEKeyboard.bleConnected));
      return true;

    }
    Mqtt.respondTrue(id);
    return true;
  }
 return false; // false means not handled
}

void BLEKeyboardPlugin::destroy() {
  BLEDevice::deinit(true);
}

#if ENABLE_I2C_OLED_DISPLAY_PLUGIN
//  void BLEKeyboardPlugin::addFramesAndOverlays() { }
#endif

#endif // CONFIG_ENABLE_BLE_KEYBOARD_PLUGIN
