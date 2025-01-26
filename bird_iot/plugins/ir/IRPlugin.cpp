#include "IRPlugin.h"

#if CONFIG_ENABLE_IR_PLUGIN

#include "include/common.h"

static const char* TAG = "IR";

IRPlugin::IRPlugin(int pin) 
    : IotPlugin("IR Plugin") {
  this->pin = pin;
}

bool IRPlugin::setup() {
  REQUIRE_VALID_OUTPUT_PIN(pin);

  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
  return true;
}

void IRPlugin::onMqttConnected() {
  Mqtt.subscribe(IR_MQTT_TOPIC);
}

// This procedure sends a 38KHz pulse to the pin for a certain # of microseconds.
void IRPlugin::mark(long micros) {
  // we'll count down from the number of microseconds we are told to wait
  cli();  // this turns off any background interrupts

  while (micros > 0) {
    // 38 kHz is about 13 microseconds high and 13 microseconds low
    digitalWrite(pin, HIGH);  // this takes about 1 microseconds to happen
    delayMicroseconds(12);          // hang out for 12 microseconds
    digitalWrite(pin, LOW);   // this also takes about 1 microseconds
    delayMicroseconds(12);          // hang out for 12 microseconds

    // so 26 microseconds altogether
    micros -= 26;
  }

  sei();  // this turns them back on
}

void IRPlugin::space(long micros) {
  delayMicroseconds(micros);
}

// markHeader - microseconds leading HIGH pulse burst
// spaceHeader - microseconds leading LOW pulse
// mark0 - microseconds HIGH pulse for logical 0
// space0 - microseconds LOW pulse for logical 0
// mark1 - microseconds HIGH pulse for logical 1
// space1 - microseconds LOW pulse for logical 1
// markFooter - final microseconds HIGH pulse to signify end of transmission
// spaceFooter - optional final microseconds LOW pulse to signify end of transmission
void IRPlugin::send_generic(const char* code, const int bits,
                            const int markHeader, const int spaceHeader,
                            const int mark0, const int space0,
                            const int mark1, const int space1,
                            const int markFooter, const int spaceFooter) {

//  setStatusColor(PURPLE);
  LOGI(TAG, "Sending IR Code: " << code);
//  enableStatusLed();
  mark(markHeader);
  space(spaceHeader);

  int offset = bits - strlen(code);
  for (int i = 0; i < bits; i++) {
    if (i < offset || code[i - offset] == '0') {
      mark(mark0);
      space(space0);
    } else {
      mark(mark1);
      space(space1);
    }
  }

  mark(markFooter);
  if (spaceFooter > 0) {
    space(spaceFooter);
  }
//  setStatusColor(ONLINE);
}

void IRPlugin::send_lg_ac(const char* code, const int bits) {
  // These were found using an IR sniffer
  send_generic(code, bits, 8271, 4298, 439, 647, 439, 1709, 439, 0);
}

void IRPlugin::send_nec(const char* code, const int bits) {
  // http://techdocs.altium.com/display/FPGA/NEC+Infrared+Transmission+Protocol#
  //  562 is actually 562.5 us
  // 1687 is actually 1.6875 ms
  send_generic(code, bits, 9000, 4500, 562, 562, 562, 1687, 562, 0);
}

void IRPlugin::sendIRCode(const char* code, const int bits, const char* protocol) {
  if (strcmp(protocol, "ac") == 0) {
    send_lg_ac(code, bits);
  } else if (strcmp(protocol, "nec") == 0) {
    send_nec(code, bits);
  } else {
    LOGI(TAG, "error, unknown protocol: " << protocol);
  }
}

bool IRPlugin::handleMqttMessage(const char *topic, const int id, const char *cmd, const JsonDocument& json) {
  if (strcmp(topic, IR_MQTT_TOPIC) != 0) {
    return false;
  }

  if (strcmp(cmd, "send") == 0) {
    getJsonProperty(const char* code, "c");
    getJsonProperty(const int bits, "b");
    getJsonProperty(const char* protocol, "p");
    sendIRCode(code, bits, protocol);
  } else {
    LOGI(TAG, "unknown command");
    return false;
  }

  Mqtt.respondTrue(id);
  return true;
}

#endif // CONFIG_ENABLE_IR_PLUGIN
