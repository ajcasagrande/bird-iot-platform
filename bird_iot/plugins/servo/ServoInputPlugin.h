#pragma once
#include "sdkconfig.h"

#if CONFIG_ENABLE_SERVO_INPUT_PLUGIN

#include "common.h"
#include "include/builtin.h"
#include "driver/rmt.h"

struct ServoConfig {
  uint16_t min, center, max, deadzone;
  uint16_t absoluteMin, absoluteMax;
  float scale;
};

// receiver pulse length ranges from 8000 to 16000 centered around 12000
const ServoConfig RCInputConfig = {8800, 12000, 15200, 10, 8000, 16000, 1.f};

struct ServoChannel {
  const char* name;
  uint8_t channel;
  uint8_t pin;
  ServoConfig cfg;
  volatile uint16_t prevValue;
  volatile uint16_t value;
  volatile bool changed;

  // returns values between -1 and 1.
  // -100 is 100% to the left
  // 0 is perfect center
  // 100 is 100% to the right
  float duty() {
    uint16_t diff;
    float sign;

    if (value < cfg.center) {
      if (value <= cfg.absoluteMin) {
        value = cfg.absoluteMin;
      }
      diff = cfg.center - value;
      sign = -100.f;

    } else {
      if (value >= cfg.absoluteMax) {
        value = cfg.absoluteMax;
      }
      diff = value - cfg.center;
      sign = 100.f;
    }

    if (diff <= cfg.deadzone) {
      return 0.f;
    }
    return sign * ((float)diff / (float)(cfg.center - cfg.min));
  }
};

#define RMT_TICK_PER_US 8
// determines how many clock cycles one "tick" is
// [1..255], source is generally 80MHz APB clk
#define RMT_RX_CLK_DIV (80000000/RMT_TICK_PER_US/1000000)
// time before receiver goes idle
#define RMT_RX_MAX_US 3500

class ServoInputPlugin : public IotPlugin {
public:
  std::vector<ServoChannel*> channels;
  VoidTask *task;

  ServoInputPlugin();

  void addChannel(const char* name, uint8_t pin, ServoConfig cfg) {
    channels.push_back(new ServoChannel{name, (uint8_t)(channels.size() + 1), pin, cfg, cfg.center, cfg.center, false});
  }

  uint8_t numChannels() {
    return (uint8_t)channels.size();
  }

  bool enabled() {
    return !channels.empty();
  }

  bool setup() override;
  bool start() override;
//  void onWifiConnected() override;
//  void onWifiDisconnected() override;
//  void onMqttConnected() override;
//  void onMqttDisconnected() override;
//  bool handleMqttMessage(const char *topic, int id, const char *cmd, const JsonDocument& json) override;
  bool handleCommand(const std::string& cmd) override;
#if CONFIG_ENABLE_I2C_OLED_DISPLAY_PLUGIN
//  void addFramesAndOverlays() override;
#endif
};

extern ServoInputPlugin ServoInput;

#endif // CONFIG_ENABLE_SERVO_INPUT_PLUGIN
