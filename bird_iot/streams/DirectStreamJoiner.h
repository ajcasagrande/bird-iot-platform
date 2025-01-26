#pragma once

#include "include/builtin.h"
#include "Lockable.h"

class DirectStreamJoinerClass : public Print, public RecursiveLockable {
public:
  size_t write(uint8_t c) override;
  size_t write(const uint8_t *buffer, size_t size) override;
};


extern DirectStreamJoinerClass DirectStreamJoiner;
