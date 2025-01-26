#include "RFRawPlugin.h"
#if CONFIG_ENABLE_RF_RAW_PLUGIN

static const char* TAG = "RF Raw Task";

static void _execute(RFRawPlugin *plugin) {
  plugin->execute();
}

RFRawPlugin::RFRawPlugin(uint8_t _pin) : IotPlugin("RF Raw Plugin") {
  this->rxPin = _pin;
  task = new Task<RFRawPlugin>("RF Raw Plugin", this, _execute);
}

bool RFRawPlugin::setup() {
  pinMode(this->rxPin, INPUT_PULLDOWN);
  return task->configure(100, _2p5, MEDIUM_PRIORITY);
}

bool RFRawPlugin::start() {
  return task->start();
}

void IRAM_ATTR RFRawPlugin::isr(void* raw) {
  auto self = static_cast<RFRawPlugin*>(raw);
  const unsigned long time = micros();
  self->timings[self->pos] = time - self->lastTime;
  self->lastTime = time;
  if (++self->pos > CONFIG_RF_RAW_SAMPLE_SIZE-1) {
    self->pos = 0;
  }
}

void RFRawPlugin::execute() {
  memset(this->timings, 0, CONFIG_RF_RAW_SAMPLE_SIZE * sizeof(unsigned int));
  this->lastTime = 0;
  this->pos = 0;

  LOGI(TAG, "RF Raw Sniff in 5...");
  taskDELAY(1000);
  LOGI(TAG, "RF Raw Sniff in 4...");
  taskDELAY(1000);
  LOGI(TAG, "RF Raw Sniff in 3...");
  taskDELAY(1000);
  LOGI(TAG, "RF Raw Sniff in 2...");
  taskDELAY(1000);
  LOGI(TAG, "RF Raw Sniff in 1...");
  taskDELAY(1000);
  LOGI(TAG, "RF Raw Sniff Go!");

  attachInterruptArg(this->rxPin, &RFRawPlugin::isr, this, CHANGE);

  taskDELAY(2000);

  detachInterrupt(this->rxPin);

  int finalstate = digitalRead(this->rxPin);

  for (unsigned int i = this->pos + finalstate; i < CONFIG_RF_RAW_SAMPLE_SIZE; i++) {
    PUTS(this->timings[i] << ",");
  }

  for (unsigned int i = 0; i < this->pos; i++) {
    PUTS(this->timings[i] << ",");
  }

  PUTS(endl);
}

//  void RFRawPlugin::onWifiConnected() { }
//  void RFRawPlugin::onWifiDisconnected() { }
//  void RFRawPlugin::onMqttConnected() { }
//  void RFRawPlugin::onMqttDisconnected() { }
//  bool RFRawPlugin::handleMqttMessage(const char *topic, int id, const char *cmd, const JsonDocument& json) {
//    return false; // false means not handled
//  }
//bool RFRawPlugin::handleCommand(const std::string& cmd) {
//  if (cmd == "R Task") {
//    PUTLN("");
//
//  } else {
//    return false; // false means not handled
//  }
//
//  return true;
//}
#if ENABLE_I2C_OLED_DISPLAY_PLUGIN
//  void RFRawPlugin::addFramesAndOverlays() { }
#endif

#endif // CONFIG_ENABLE_RF_RAW_PLUGIN
