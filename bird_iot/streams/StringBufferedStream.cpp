#include "StringBufferedStream.h"

#include "WebsocketWrapper.h"

void StringBufferedStream::flush() {
  if (WebsocketWrapper::isActive()) {
    xSemaphoreTakeRecursive(mutex, portMAX_DELAY);
    sbuf.flush();
    std::string s = sbuf.str();
    int length = s.length();
    int maxLen = CONFIG_MBEDTLS_SSL_OUT_CONTENT_LEN - WEBSOCKETS_MAX_HEADER_SIZE;
    if (length > 0) {
      if (length < maxLen) {
        WebsocketWrapper::sendTXT((uint8_t *)s.c_str(), s.length(), false);
      } else {
        for (int i=0; i < length; i += maxLen) {
          WebsocketWrapper::sendTXT(((uint8_t *)s.c_str()) + i, min(maxLen, length - i), false);
        }
      }
    }
    reset();
    xSemaphoreGiveRecursive(mutex);
  } else {
    reset();
  }
}

void StringBufferedStream::reset() {
  xSemaphoreTakeRecursive(mutex, portMAX_DELAY);
  sbuf.clear();
  sbuf.str(std::string());
  sbuf.clear();
  xSemaphoreGiveRecursive(mutex);
}

size_t StringBufferedStream::write(uint8_t c) {
  if (WebsocketWrapper::isActive()) {
    xSemaphoreTakeRecursive(mutex, portMAX_DELAY);
    sbuf.write((const char *)&c, 1);
    xSemaphoreGiveRecursive(mutex);
  }
  return 1;
}

size_t StringBufferedStream::write(const uint8_t *buff, size_t size) {
  if (WebsocketWrapper::isActive()) {
    xSemaphoreTakeRecursive(mutex, portMAX_DELAY);
    sbuf.write((const char *)buff, size);
    xSemaphoreGiveRecursive(mutex);
  }
  return size;
}

