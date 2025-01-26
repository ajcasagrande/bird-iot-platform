#pragma once

#include <sstream>
#include "include/builtin.h"

class StringBufferedStream : public Print {
public:
  StringBufferedStream() { reset(); }

  size_t write(uint8_t c) override;
  size_t write(const uint8_t *buffer, size_t size) override;
  void flush();
  void reset();

private:
  std::ostringstream sbuf;
  QueueHandle_t mutex = xSemaphoreCreateMutex();
};

