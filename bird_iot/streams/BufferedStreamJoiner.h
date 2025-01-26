#pragma once

#include <Print.h>
#include "TaskClass.h"
#include "IotPlugin.h"
#include "streams/StringBufferedStream.h"
#include "rtos/Lockable.h"

class BufferedStreamJoinerClass : public Print, public IotPlugin, public RecursiveLockable {
public:
  StringBufferedStream bufferedStream;

  BufferedStreamJoinerClass() : IotPlugin("Buffered Stream") {}

  bool setup() override;
  bool start() override;
  size_t write(uint8_t c) override;
  size_t write(const uint8_t *buffer, size_t size) override;

private:
  VoidTask *task;
};

extern BufferedStreamJoinerClass BufferedStreamJoiner;
