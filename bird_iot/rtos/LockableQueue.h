#pragma once

#include <vector>
#include "Lockable.h"
#include "lock_macros.h"

template<class T>
class LockableQueue : public ExclusiveLockable {
public:
  bool empty() {
    bool empty;
    TRY_LOCK(*this,
    empty = data.empty();
    , empty = true;);
    return empty;
  }

  bool push_back(T* item) {
    bool res;
    TRY_LOCK(*this,
      data.push_back(item);
    res = true;
    , res = false;);
    return res;
  }

  T* pop() {
    T* item = nullptr;
    TRY_LOCK(*this,
        item = data.back();
        data.pop_back();
    ,);
    return item;
  }

  std::vector<T*>& getData() { return data; }

  void clear() {
    data.clear();
  }

protected:
  std::vector<T*> data;
};

