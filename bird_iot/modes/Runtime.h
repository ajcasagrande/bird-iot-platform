#pragma once

#include "RunMode.h"

#define registerIf(conditional, plugin)       if (conditional) App.registerPlugin(plugin)
#define registerIfPin(optionalPin, plugin)    registerIf(isPin(optionalPin), plugin)

class RuntimeClass : public RunMode {
public:
  bool activate() override;
};

extern RuntimeClass Runtime;
