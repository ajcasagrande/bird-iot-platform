#include "streams/DirectStreamJoiner.h"

#include "WebsocketWrapper.h"
#include "HardwareSerial.h"

DirectStreamJoinerClass DirectStreamJoiner;

size_t DirectStreamJoinerClass::write(uint8_t c) {
  Serial.write(c);
  WebsocketWrapper::sendTXT(&c, 1, false);
  return 1;
}

size_t DirectStreamJoinerClass::write(const uint8_t *buff, size_t size) {
  Serial.write(buff, size);
  WebsocketWrapper::sendTXT((uint8_t *)buff, size, false);
  return size;
}
