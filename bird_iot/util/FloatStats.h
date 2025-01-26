#pragma once

// todo: template this mofo

class FloatStats {
public:
  explicit FloatStats(const char*);

  const char* name;

  double total;
  float min;
  float max;
  double samples;
  long invalidSamples;

  float prev = 0.0;
  float current = 0.0;
  float changed_by = 0.0;
  bool changed = false;

  // returns the value back, so it can be used in a return call
  float addValue(float);
  double getAverage(int);
  void reset();
};

