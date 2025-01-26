#include "NeoPixelDriver.h"

#if CONFIG_ENABLE_NEOPIXEL_DRIVER

#include "include/common.h"
#include "neo_animations.h"

static const char* TAG = "NeoPixel";

static void _execute(NeoPixelDriver *driver) {
  driver->execute();
}

NeoPixelDriver::NeoPixelDriver(uint8_t pin, uint16_t count) : IotPlugin("NeoPixel Driver"), count(count) {
  pixels = new NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod>(count, pin);
  task = new Task<NeoPixelDriver>("NeoPixel", this, _execute);
}

bool NeoPixelDriver::setup() {
  pixels->Begin();

  // just pick some colors
  for (uint16_t pixel = 0; pixel < count; pixel++) {
    pixels->SetPixelColor(pixel, RgbColor(random(255), random(255), random(255)));
  }

  mode = READY;
  animationMode = new BasicEasingAnimation(this);

  return task->configure(10, _2k, MEDIUM_HIGH_PRIORITY, tskNO_AFFINITY, true, false);
}

bool NeoPixelDriver::start() {
  return task->start();
}

void NeoPixelDriver::set(uint8_t index, RGB color) {
  LOGI(TAG, "Set neo pixel index " << index << " color: r: " << color.r << ", g: " << color.g << ", b: " << color.b);
  pixels->SetPixelColor(index, RgbColor(color.r, color.g, color.b));
  pixels->Show();
}

void NeoPixelDriver::setAll(RGB color) {
  LOGI(TAG, "Set all neo pixels color: r: " << color.r << ", g: " << color.g << ", b: " << color.b);
  auto c = RgbColor(color.r, color.g, color.b);
  for (uint16_t i=0; i < count; i++) {
    pixels->SetPixelColor(i, c);
  }
  pixels->Show();
}

void NeoPixelDriver::execute() {
  switch (mode) {
  case PAUSED:
    return;

  case READY:
    if (animationMode != nullptr) {
      mode = ANIMATING;
      animationMode->setup();
    } else {
      mode = STEADY;
    }
    break;

  case ANIMATING:
    if (animationMode != nullptr) {
      animationMode->loop();
    }
    break;

  case STEADY:
  default:
    break;
  }
}

void NeoPixelDriver::onMqttConnected() {
  Mqtt.subscribe(NEOPIXEL_MQTT_TOPIC);
}

bool NeoPixelDriver::handleMqttMessage(const char *topic, const int id, const char *cmd, const JsonDocument& json) {
  if (strcmp(topic, NEOPIXEL_MQTT_TOPIC) != 0) {
    return false;
  }

  if (strcmp(cmd, "color") == 0 || strcmp(cmd, "set_neo_pixel") == 0) {
    getJsonProperty(const int r, "r");
    getJsonProperty(const int g, "g");
    getJsonProperty(const int b, "b");
    setAll(RGB(r, g, b));
  } else {
    LOGI(TAG, "unknown command");
    return false;
  }

  Mqtt.respondTrue(id);
  return true;
}

void NeoPixelDriver::pause() {
  switch (mode) {
    case ANIMATING:
      if (animationMode != nullptr) {
        animationMode->pause();
      }
      break;
    case PAUSED:
      return;
    default:
      break;
  }
  mode = PAUSED;
}

void NeoPixelDriver::resume() {
  if (mode != PAUSED) {
    return;
  }
  mode = READY;
}


void printColorCommandUsage() {
  PUTLN(LOG_COLOR_W << "Usage: " << BOLD_STYLE << "color [index1] [index2]... r g b" << LOG_RESET_COLOR);
}

bool NeoPixelDriver::handleCommand(const std::string& cmd) {
  // color [idx1] [idx2]... r g b
  // color 255 0 0  -> color all red
  // color 1 255 0 0  -> color pixel 1 red
  // color 1 3 5 255 0 0 -> color pixels 1, 3 and 5 red
  if (cmd.find("color") == 0) {
    std::vector<std::string> out;
    tokenize(cmd, ' ', out);
    if (out.size() >= 4) {
      uint8_t r, g, b;
      char *endptr;
      r = strtol(out[out.size()-3].c_str(), &endptr, 10);
      if (*endptr != '\0') {
        printColorCommandUsage();
        return true;
      }
      g = strtol(out[out.size()-2].c_str(), &endptr, 10);
      if (*endptr != '\0') {
        printColorCommandUsage();
        return true;
      }
      b = strtol(out[out.size()-1].c_str(), &endptr, 10);
      if (*endptr != '\0') {
        printColorCommandUsage();
        return true;
      }

      RGB color = RGB(r, g, b);
      if (out.size() == 4) {
        setAll(color);
      } else {
        for (int i=1; i < out.size()-3; i++) {
          uint8_t idx = strtol(out[i].c_str(), &endptr, 10);
          if (*endptr != '\0') {
            printColorCommandUsage();
            return true;
          }
          set(idx, color);
        }
      }
    } else {
      printColorCommandUsage();
    }

  } else {
    return false; // false means not handled
  }

  return true;
}

#endif // CONFIG_ENABLE_NEOPIXEL_DRIVER
