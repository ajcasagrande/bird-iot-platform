#pragma once

class RunMode {
protected:
  bool active = false;
public:
  bool isActive() { return active; }
  virtual bool activate() = 0;
};

