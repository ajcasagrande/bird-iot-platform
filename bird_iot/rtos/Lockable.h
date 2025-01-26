#pragma once

#include "sdkconfig.h"
#include "include/builtin.h"
#include "rtos.h"

class Lockable {
public:
  virtual bool acquire(TickType_t xTicksToWait) = 0;
  virtual bool unlock() = 0;
  bool lock() { return acquire(uxSecondsTicks(CONFIG_BIRD_IOT_LOCK_WAIT_SECONDS)); }
  void startLockTrace() { traceLocks = true; }
  void stopLockTrace() { traceLocks = false; }
protected:
  bool traceLocks = false;
};

class RecursiveLockable : public Lockable {
public:
  bool acquire(TickType_t xTicksToWait) override;
  bool unlock() override;
protected:
  SemaphoreHandle_t mutex = xSemaphoreCreateRecursiveMutex();
};

class ExclusiveLockable : public Lockable {
public:
  bool acquire(TickType_t xTicksToWait) override;
  bool unlock() override;
protected:
  QueueHandle_t mutex = xSemaphoreCreateMutex();
};
