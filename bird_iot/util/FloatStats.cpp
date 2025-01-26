#include "FloatStats.h"

#include "include/logging.h"
#include "util/helpers.h"

//static const char* TAG = "FloatStats";

FloatStats::FloatStats(const char *name) {
  this->name = name;
  this->reset();
}

void FloatStats::reset() {
  total = 0.0;
  min = 9999.0;
  max = -9999.0;
  samples = 0.0;
  invalidSamples = 0;
  // do not reset prev or current!
}

float FloatStats::addValue(float value) {
  changed_by = abs(current - value);
  changed = changed_by > __FLT_EPSILON__;

  prev = current;
  current = value;

  samples++;
  total += value;

  if (value > max) {
    max = value;
  }

  if (value < min) {
    min = value;
  }

  return value;
}

double FloatStats::getAverage(int places) {
  auto avg = (double)(total / samples);
  LOGD(name, name << "Stats: total: " << total << ", samples: " << samples << ", min: " << min << ", max " << max << ", avg: " << avg);
  return roundTo(avg, places);
}
