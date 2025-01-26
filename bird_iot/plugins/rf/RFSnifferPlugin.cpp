#include "RFSnifferPlugin.h"
#if CONFIG_ENABLE_RF_SNIFFER_PLUGIN

#include "rtos/xprintf.h"

static const char* TAG = "RF Sniffer";

static void _execute(RFSnifferPlugin *plugin) {
  plugin->execute();
}

RFSnifferPlugin::RFSnifferPlugin(uint _freq, uint8_t _pin) : IotPlugin("RFSniffer Plugin") {
  this->freq = _freq;
  this->rxPin = _pin;

  task = new Task<RFSnifferPlugin>("RF Sniffer", this, _execute);
}

bool RFSnifferPlugin::setup() {
  // pinMode(this->rxPin, INPUT_PULLDOWN);
  pinMode(this->rxPin, INPUT_PULLUP);
  rf.enableReceive(rxPin);
  return task->configure(10, _3k, MEDIUM_HIGH_PRIORITY);
}

bool RFSnifferPlugin::start() {
  return task->start();
}

void RFSnifferPlugin::execute() {
  if (!rf.available()) {
    return;
  }

  uint bits = rf.getReceivedBitlength();
  if (bits < CONFIG_RF_SNIFF_MIN_BIT_LENGTH) {
    return;
  }

  uint32_t value = rf.getReceivedValue();
  uint pulse = rf.getReceivedDelay();

  uint timings[64]; // get a copy of the received timings before they are overwritten
  uint count = (2 * bits) + 2;
  if (count > 64) {
    count = 64;
  }
  for (uint i = 0; i < count; i++) {
    timings[i] = rf.getReceivedRawdata()[i];
  }

  uint offset = abs((int)rf.getReceivedLevelInFirstTiming() - (int)rf.getReceivedInverted());

  uint32_t duration = 0;
  for (uint i = 1 + offset; i < count - 1 + offset; i++) {
    duration += timings[i];
  }

  uint avgDuration = lround((double)duration / bits);
  uint ratio = lround((double)(avgDuration - pulse) / pulse);

  uint syncHigh = lround(timings[offset == 0 ? (2 * bits + 1) : 0] / (double)pulse);
  uint syncLow = lround(timings[offset == 0 ? 0 : 1] / (double)pulse);

  char protocol[50];
  xsnprintf(protocol, 50, "{%u,{%u,%u},{1,%u},{%u,1},%s}",
            pulse, syncHigh, syncLow, ratio, ratio,
            rf.getReceivedInverted() ? "true" : "false");

  char hexValue[20];
  xsnprintf(hexValue, 20, "0x%X", value);

  const size_t capacity = JSON_ARRAY_SIZE(2 * bits + 2 - 1 + offset) + JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(8);
  DynamicJsonDocument doc(capacity);
  doc["cmd"] = "rf_sniff";
  JsonObject result = doc.createNestedObject("result");
  result["freq"] = freq;
  result["value"] = hexValue;
  result["bits"] = bits;
  result["pulse"] = pulse;
  result["duration"] = duration;
  result["ratio"] = ratio;
  result["protocol"] = protocol;

  // raw signal timings in MICRO-seconds
  // can be plotted using https://github.com/sui77/SimpleRcScanner
  JsonArray result_timings = result.createNestedArray("timings");
  for (uint i = 0; i < 2 * bits + 2 - 1 + offset; i++) {
    result_timings.add(timings[i]);
  }

  Mqtt.publish(Mqtt.topics.rf_data, doc);

  rf.resetAvailable();
}

void RFSnifferPlugin::doRawRFScan() {
  memset(this->rawTimings, 0, CONFIG_RF_RAW_SAMPLE_SIZE * sizeof(unsigned int));
  this->rawLastTime = 0;
  this->rawPos = 0;

  LOGI(TAG, "RF Raw Sniff in 2...");
  taskDELAY(1000);
  LOGI(TAG, "RF Raw Sniff in 1...");
  taskDELAY(1000);
  LOGI(TAG, "RF Raw Sniff Go!");

  rf.disableReceive();
  attachInterruptArg(this->rxPin, &RFSnifferPlugin::isr, this, CHANGE);

  taskDELAY(2000);

  detachInterrupt(this->rxPin);
  rf.enableReceive(rxPin);

  int finalstate = digitalRead(this->rxPin);

  for (unsigned int i = this->rawPos + finalstate; i < CONFIG_RF_RAW_SAMPLE_SIZE; i++) {
    PUTS(this->rawTimings[i] << ",");
  }

  for (unsigned int i = 0; i < this->rawPos; i++) {
    PUTS(this->rawTimings[i] << ",");
  }

  PUTS(endl);
}

void IRAM_ATTR RFSnifferPlugin::isr(void* sniffer) {
  auto self = static_cast<RFSnifferPlugin*>(sniffer);
  const unsigned long time = micros();
  self->rawTimings[self->rawPos] = time - self->rawLastTime;
  self->rawLastTime = time;
  if (++self->rawPos > CONFIG_RF_RAW_SAMPLE_SIZE-1) {
    self->rawPos = 0;
  }
}

bool RFSnifferPlugin::handleCommand(const std::string& cmd) {
  if (cmd == "rf raw") {
    doRawRFScan();
  } else {
    return false; // false means not handled
  }

  return true;
}

#endif // CONFIG_ENABLE_RF_SNIFFER_PLUGIN
