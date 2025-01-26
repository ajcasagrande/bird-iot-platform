#include "RcLightsPlugin.h"
#if CONFIG_ENABLE_RC_LIGHTS_PLUGIN

static const char* TAG = "RC Lights";

RcLightsPlugin::RcLightsPlugin(NeoPixelDriver* neoPixelDriver) : IotPlugin("Rc Lights Plugin"), driver(neoPixelDriver) { }

bool RcLightsPlugin::setup() {
  return true;
}
bool RcLightsPlugin::start() {

  // pause any animations
  driver->pause();

  // setup all static colors
  for (int i=0; i < App.profile.neoPixelColors.size(); i++) {
    driver->set(i, App.profile.neoPixelColors[i]);
  }

  return true;
}
//void RcLightsPlugin::onWifiConnected() { }
//void RcLightsPlugin::onWifiDisconnected() { }
//void RcLightsPlugin::onMqttConnected() { }
//void RcLightsPlugin::onMqttDisconnected() { }
//bool RcLightsPlugin::handleMqttMessage(const char *topic, int id, const char *cmd, const JsonDocument& json) {
//  return false; // false means not handled
//}
//bool RcLightsPlugin::handleCommand(const std::string& cmd) {
//  if (cmd == "Rc Basic") {
//    PUTLN("");
//
//  } else {
//    return false; // false means not handled
//  }
//
//  return true;
//}
#if ENABLE_I2C_OLED_DISPLAY_PLUGIN
//void RcLightsPlugin::addFramesAndOverlays() { }
#endif

#endif // CONFIG_ENABLE_RC_LIGHTS_PLUGIN
