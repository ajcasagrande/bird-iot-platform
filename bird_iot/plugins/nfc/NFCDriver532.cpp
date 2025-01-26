#include "NFCDriver532.h"
#if CONFIG_ENABLE_NFC_DRIVER_532

static const char* TAG = "NFC 532";

static void _execute(NFCDriver532 *driver) {
  driver->execute();
}

NFCDriver532::NFCDriver532() : IotPlugin("NFC Driver PN532") {
  task = new Task<NFCDriver532>("NFC 532", this, _execute);
}

bool NFCDriver532::setup() {
  LOGI(TAG, "create pn532 object");
  pn532i2c = new PN532_I2C(Wire);
  nfc = new PN532(*pn532i2c);
  LOGI(TAG, "call nfc begin");
  nfc->begin();
  LOGI(TAG, "get firmware information");
  uint32_t fw = nfc->getFirmwareVersion();
  LOGI(TAG, "Found chip PN5 " << _HEX((fw>>24) & 0xFF));
  LOGI(TAG, "Firmware ver. " << _DEC((fw>>16) & 0xFF) << "." << _DEC((fw>>8) & 0xFF));

  return task->configure(10, _3k, MEDIUM_PRIORITY, CORE_1, false, false);
}

bool NFCDriver532::start() {
  return nfc->SAMConfig()
         && task->start();
}

void NFCDriver532::execute() {
  uint8_t success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
  uint8_t uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)

  // Wait for an ISO14443A type cards (Mifare, etc.).  When one is found
  // 'uid' will be populated with the UID, and uidLength will indicate
  // if the uid is 4 bytes (Mifare Classic) or 7 bytes (Mifare Ultralight)
  success = nfc->readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);

  if (success) {
    // Display some basic information about the card
    LOGI(TAG, "Found an ISO14443A card");
    LOGI(TAG, "  UID Length: " << _DEC(uidLength) << " bytes");
    LOGI(TAG, "  UID Value: ");
    PN532::PrintHex(uid, uidLength);

    if (uidLength == 4) {
      // We probably have a Mifare Classic card ...
      uint32_t cardid = uid[0];
      cardid <<= 8;
      cardid |= uid[1];
      cardid <<= 8;
      cardid |= uid[2];
      cardid <<= 8;
      cardid |= uid[3];
      LOGI(TAG, "Seems to be a Mifare Classic card #" << _HEX(cardid));
    }
  }
}

//  void NFCDriver532::onWifiConnected() { }
//  void NFCDriver532::onWifiDisconnected() { }
//  void NFCDriver532::onMqttConnected() { }
//  void NFCDriver532::onMqttDisconnected() { }
//  bool NFCDriver532::handleMqttMessage(const char *topic, int id, const char *cmd, const JsonDocument& json) {
//   return false; // false means not handled 
// }
//  bool NFCDriver532::handleCommand(const std::string& cmd) {
//   return false; // false means not handled 
// }
#if ENABLE_I2C_OLED_DISPLAY_PLUGIN
//  void NFCDriver532::addFramesAndOverlays() { }
#endif

#endif // CONFIG_ENABLE_NFC_DRIVER_532
