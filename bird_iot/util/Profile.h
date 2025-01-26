#pragma once
#include "sdkconfig.h"

#include <string>
#include <vector>
#include <utility>

#include <Arduino.h>
#include <Esp.h>
#include <pins_arduino.h>
#include <DHT.h>

#include "ota_common.h"
#include "util/helpers.h"
#include "include/my_types.h"
#include "ReedSwitch.h"
#include "colors.h"

#define UNKNOWN_PROFILE "unknown"
#define WIFI_SCAN_DISABLED 0

#ifndef ONE_WIRE_PIN
#define ONE_WIRE_PIN NOT_A_PIN
#endif

#define StreamProfile(profile) "Profile(id: " << profile.id << " useStaticIp: " << profile.useStaticIp \
     << " sda: " << profile.sda << " scl: " << profile.scl \
     << " oneWirePin: " << profile.oneWirePin << " rgbStatusLed: " << profile.rgbStatusLed \
     << " neoPixelPin: " << profile.neoPixelPin << " neoPixelCount: " << profile.neoPixelCount << " rf433Transmit: " \
     << profile.rf433Transmit << " rf433TxRepeat: " << profile.rf433TxRepeat << " rf433Receive: " \
     << profile.rf433Receive << " rf315Transmit: " << profile.rf315Transmit << " rf315TxRepeat: " \
     << profile.rf315TxRepeat << " rf315Receive: " << profile.rf315Receive << " soilSensorPin: " \
     << profile.soilSensorPin << " dhtPin: " << profile.dhtPin << " dhtModel: " << profile.dhtModel \
     << " irTransmitPin: " << profile.irTransmitPin << " irReceivePin: " << profile.irReceivePin << " ds18b20Index: " \
     << profile.ds18b20Index << " garageRelayPin: " << profile.garageRelayPin \
     << " gpsUartNumber: " << profile.gpsUartNumber << " gpsRxPin: " << profile.gpsRxPin \
     << " gpsTxPin: " << profile.gpsTxPin << " hunterFanTx: " << profile.hunterFanTx << " hunterFanRepeat: " \
     << profile.hunterFanRepeat << " i2cLCDChars: " << profile.i2cLCDChars << " i2cLCDLines: " << profile.i2cLCDLines \
     << " wifiScanInterval: " << profile.wifiScanInterval << " wifiScanMillisPerChannel: " \
     << profile.wifiScanMillisPerChannel << " wifiScanChannelDelay: " << profile.wifiScanChannelDelay \
     << " updateChannel: " << profile.updateChannel << ")"

class Profile {
 public:
  Profile();
  explicit Profile(std::string id);

  std::string id;

  bool useStaticIp = false;

  pin_t sda = SDA;
  pin_t scl = SCL;
  pin_t oneWirePin = ONE_WIRE_PIN;

  pin_t rgbStatusLed = NOT_A_PIN;

  pin_t neoPixelPin = NOT_A_PIN;
  // 30 LEDs per strip for my white ones
  uint8_t neoPixelCount = 0;

  pin_t rf433Transmit = NOT_A_PIN;
  uint8_t rf433TxRepeat = 15;
  pin_t rf433Receive = NOT_A_PIN;

  pin_t rfRawPin = NOT_A_PIN;
  
  pin_t rf315Transmit = NOT_A_PIN;
  uint8_t rf315TxRepeat = 15;
  pin_t rf315Receive = NOT_A_PIN;

  gpio_num_t soilSensorPin = GPIO_NUM_MAX;

  pin_t dhtPin = NOT_A_PIN;
  int dhtModel = UNDEFINED;

  pin_t irTransmitPin = NOT_A_PIN;
  pin_t irReceivePin = NOT_A_PIN;

  int ds18b20Index = UNDEFINED;

  gpio_num_t garageRelayPin = GPIO_NUM_MAX;
  std::vector<ReedSwitch> reedSwitches;

  ReedSwitch *openReedSwitch = nullptr;
  ReedSwitch *closedReedSwitch = nullptr;

  int gpsUartNumber = 1;
  // pin labelled as RX on GPS module
  gpio_num_t gpsRxPin = NOT_A_GPIO_PIN;
  // pin labelled as TX on GPS module
  gpio_num_t gpsTxPin = NOT_A_GPIO_PIN;

  pin_t hunterFanTx = NOT_A_PIN;
  int hunterFanRepeat = 5;

  uint8_t i2cLCDChars = 16;
  uint8_t i2cLCDLines = 2;

  uint32_t wifiScanInterval = WIFI_SCAN_DISABLED;
  uint32_t wifiScanMillisPerChannel = 350;
  uint32_t wifiScanChannelDelay = 2000;

  int updateChannel = SOFTWARE_CHANNEL_DEV;

  std::vector<RGB> neoPixelColors;

  pin_t sdaSlave = NOT_A_PIN;
  pin_t sclSlave = NOT_A_PIN;
  uint8_t i2cSlaveAddr = 0;

  bool i2cEnabled() { return isPin(sda) && isPin(scl); }
  bool i2cSlaveEnabled() { return isPin(sdaSlave) && isPin(sclSlave); }
  bool oneWireEnabled() { return isPin(oneWirePin); }
  bool ds18b20Enabled() { return isPin(oneWirePin) && ds18b20Index != UNDEFINED; }
  bool neoPixelEnabled() { return isPin(neoPixelPin) && neoPixelCount > 0; }
  bool dhtEnabled() { return isPin(dhtPin) && dhtModel != UNDEFINED; }
  bool dualReedEnabled() { return openReedSwitch != nullptr || closedReedSwitch != nullptr; }
  bool gpsEnabled() { return isPin(gpsRxPin) && isPin(gpsTxPin); }
  bool wifiScanEnabled() { return wifiScanInterval != WIFI_SCAN_DISABLED; }
};

Profile* findProfile();
