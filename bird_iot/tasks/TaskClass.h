#pragma once

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "include/rtos.h"
#include "include/sizes.h"
#include "include/priorities.h"
#include <functional>
#include <string>
#include <utility>

#define PRINT_TASK_STACK_INFO(x) LOGD("task", x ": task: " << _name << ", stack: " << _stackSize - uxTaskGetStackHighWaterMark(_handle))
#define PRINT_TASK_STACK_INFO_T(t, x) LOGD("task", x ": task: "<< t->_name << ", stack: " << t->_stackSize - uxTaskGetStackHighWaterMark(t->_handle))

#define PRINT_CURRENT_TASK_STACK(x) taskYIELD();LOGD(TAG, x ": " << uxTaskGetStackHighWaterMark(NULL))

class TaskClass {
public:
  TaskHandle_t _handle;
  std::string _name;
  uint32_t _iterations = 0;
  uint32_t _interval = 0;
  portBASE_TYPE _priority = 5;
  uint32_t _stackSize = _4k;
  BaseType_t _coreId = CORE_1;
  // exact timing means it computes how long it took to run <runtime> and only sleep for (_interval - <runtime>)
  // so that way if the interval is 10ms, it should fire exactly every 10ms with 0 drift as long as the <runtime>
  // never exceeds the interval
  bool _exactTiming = false;
  bool _singleShot = false;
  int _initialDelay = -1;
  // by default all tasks are paused while OTA is running to prevent transfer errors
  bool _allowDuringOTA = false;
  bool _started = false;
  bool _paused = false;
  bool _deleted = false;

public:
  explicit TaskClass(std::string name) : _name(std::move(name)) { }

  void _executeIfAllowed();
  std::string getName() { return _name; }
  uint32_t getInterval() { return _interval; }
  void setInterval(uint32_t interval) { _interval = interval; }
  bool started() { return _started; }
  void setInitialDelay(int initialDelay) { _initialDelay = initialDelay; }
  void setUseExactTiming(bool useExact) { _exactTiming = useExact; }
  bool useExactTiming() { return _exactTiming; }
  BaseType_t getCoreId() { return _coreId; }

  virtual uint32_t getStackSize() { return _stackSize; }
  uint32_t getIterations() { return _iterations; }
  bool isAllowedDuringOTA() { return _allowDuringOTA; }
  void setAllowedDuringOTA(bool allow) { _allowDuringOTA = allow; }

  bool setPriority(portBASE_TYPE priority);
  bool setStackSize(uint32_t stackSize);
  bool setCoreId(BaseType_t coreId);

  bool configure(uint32_t interval, uint32_t stackSize, portBASE_TYPE priority = MEDIUM_PRIORITY, BaseType_t coreId = CORE_1, bool useExact = false, bool allowDuringOTA = false, int initialDelay = -1);

  bool fireSingleShot(int initialDelay);

  bool start();
  bool pause();
  bool resume();
  bool remove();
  bool isPaused() { return _paused; }
  TaskHandle_t getHandle() { return _handle; }

  virtual void execute() = 0;
};

template<class T>
class Task : public TaskClass {
private:
  T *_t;
  std::function<void(T*)> _fn;
public:
  Task(const std::string& name, T *t, std::function<void(T*)> fn) : TaskClass(name), _t(t), _fn(fn) { }
  void execute() override {
    _fn(_t);
  }
};

class VoidTask : public TaskClass {
private:
  std::function<void()> _fn;
public:
  VoidTask(const char* name, std::function<void()> fn) : TaskClass(name), _fn(std::move(fn)) { }
  void execute() override {
    _fn();
  }
};
