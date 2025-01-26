#pragma once

template<class T>
class CircularBuffer {
public:
  int windowSize;
  int counter;
  T* values;

  explicit CircularBuffer(int windowSize) : windowSize(windowSize) {
    values = (T*) malloc(windowSize * sizeof(T));
  }

  int size() {
    if (counter >= windowSize) {
      return windowSize;
    }
    return counter;
  }

  void add(T value) {
    values[counter % windowSize] = value;
    ++counter;
  }

  T current() {
    return values[(counter-1) % windowSize];
  }

  double mean() {
    int count = size();
    double total = 0.0;
    for (int i = 0; i < count; ++i) {
      total += values[i];
    }
    return total / (double)count;
  }
};
