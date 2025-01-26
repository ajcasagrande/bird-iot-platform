#include "streams/BufferedStreamJoiner.h"

#include "HardwareSerial.h"

BufferedStreamJoinerClass BufferedStreamJoiner;

static void _execute() {
  BufferedStreamJoiner.bufferedStream.flush();
}

bool BufferedStreamJoinerClass::setup() {
  task = new VoidTask("Stream Buffer", _execute);
  return task->configure(100, _1p75, MEDIUM_HIGH_PRIORITY, tskNO_AFFINITY, true, true);
}

bool BufferedStreamJoinerClass::start() {
  return task->start();
}

size_t BufferedStreamJoinerClass::write(uint8_t c) {
  Serial.write(c);
  bufferedStream.write(c);
  return 1;
}

size_t BufferedStreamJoinerClass::write(const uint8_t *buff, size_t size) {
  Serial.write(buff, size);
  bufferedStream.write(buff, size);
  return size;
}

