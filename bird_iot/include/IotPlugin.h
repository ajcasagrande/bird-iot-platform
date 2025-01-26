#pragma once

#include <ArduinoJson.h>
#include <string>
#include "include/rtos.h"

class IotPlugin {
public:
  std::string name;

  explicit IotPlugin(std::string name) : name(std::move(name)) { }
  IotPlugin() : IotPlugin("Unknown Plugin") { }

  // optional
  virtual bool setup() { return true; }
  // optional
  virtual bool start() { return true; }

  virtual void onWifiConnected() { }
  virtual void onWifiDisconnected() { }
  virtual void onMqttConnected() { }
  virtual void onMqttDisconnected() { }

  virtual bool handleMqttMessage(const char *topic, int id, const char *cmd, const JsonDocument& json) { return false; } // false means not handled
  virtual bool handleCommand(const std::string& cmd) { return false; }

  // Add UI Frames and Overlays for OLED displays
  virtual void addFramesAndOverlays() { }
};
