#include "Profile.h"

#include <utility>

#include "include/common.h"
#include "ServoInputPlugin.h"
#include "spektrum.h"

#define isDevice(otherId) (p->id == otherId)

static const char* TAG = "Profile";

Profile::Profile() : Profile(UNKNOWN_PROFILE) {
}

Profile::Profile(std::string id) {
  this->id = std::move(id);
}

Profile* findProfile() {
  LOGI(TAG, "Finding device profile...");
  auto *p = new Profile(deviceId());

  if isDevice("esp32-5927d4") {
    return p;
  }

  if isDevice("esp32-999118") {
    p->updateChannel = SOFTWARE_CHANNEL_STABLE;
    p->garageRelayPin = GPIO_NUM_25;
//    p->closedReedSwitch = new ReedSwitch(GPIO_NUM_12, true, INPUT_PULLUP);
//    p->openReedSwitch = new ReedSwitch(GPIO_NUM_13, true, INPUT_PULLUP);
    return p;
  }

  if isDevice("esp32-f06320") {
//    p->rf315Transmit = GPIO_NUM_27;
//    p->soilSensorPin = GPIO_NUM_36;
//
//    p->oneWirePin = GPIO_NUM_17;
//    p->ds18b20Index = 0;

    p->rf433Receive = GPIO_NUM_36;
    return p;
  }

  if isDevice("esp32-998fec") {
    // p->gpsUartNumber = 1;
    // p->gpsTxPin = GPIO_NUM_26;
    // p->gpsRxPin = GPIO_NUM_27;

    // p->neoPixelPin = GPIO_NUM_25;
    // p->neoPixelCount = 30;

//    p->sdaSlave = GPIO_NUM_26;
//    p->sclSlave = GPIO_NUM_27;
//    p->i2cSlaveAddr = TELE_DEVICE_GYRO;

    return p;
  }

  if isDevice("esp32-998f60") {
//    p->wifiScanInterval = 30000;
// #if CONFIG_ENABLE_SERVO_INPUT_PLUGIN
//     ServoInput.addChannel("Steering", GPIO_NUM_36, RCInputConfig);
//     ServoInput.addChannel("Throttle", GPIO_NUM_37, RCInputConfig);
// #endif
    p->rf433Receive = GPIO_NUM_36;
    p->oneWirePin = GPIO_NUM_33;
    return p;
  }

  if isDevice("esp32-998fb4") {
    //  p->rfRawPin = GPIO_NUM_27;
    p->rf433Receive = GPIO_NUM_27;
    p->rf433Transmit = GPIO_NUM_12;

    // p->sdaSlave = GPIO_NUM_26;
    // p->sclSlave = GPIO_NUM_27;
    // p->i2cSlaveAddr = TELE_DEVICE_GYRO;

//    p->neoPixelPin = GPIO_NUM_25;
//    p->neoPixelCount = 30;
    return p;
  }

  if isDevice("esp32-f05e50") {
    p->gpsUartNumber = 1;
    p->gpsTxPin = GPIO_NUM_26;
    p->gpsRxPin = GPIO_NUM_27;

#if CONFIG_ENABLE_SERVO_INPUT_PLUGIN
    ServoInput.addChannel("Steering", GPIO_NUM_36, RCInputConfig);
#endif
    return p;
  }

  if isDevice("esp32-f05ff4") {
    p->rf315Receive = GPIO_NUM_27;
    p->rf433Transmit = GPIO_NUM_25;
    return p;
  }

  if isDevice("esp32-f064c0") {
    for (int i = 0; i < 18; i++) {
      p->neoPixelColors.push_back(LED_BLUE);
    }

    p->neoPixelPin = GPIO_NUM_25;
    // get neo pixel count based on colors
    p->neoPixelCount = p->neoPixelColors.size();

//#if CONFIG_ENABLE_SERVO_INPUT_PLUGIN
//    ServoInput.addChannel("Steering", GPIO_NUM_36, RCInputConfig);
//    ServoInput.addChannel("Throttle", GPIO_NUM_37, RCInputConfig);
//#endif
    return p;
  }

  return new Profile(UNKNOWN_PROFILE);
}

