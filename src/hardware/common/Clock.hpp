/*!
 * @file
 * @brief
 */

#ifndef Clock_hpp
#define Clock_hpp

extern "C" {
#include "clock.h"
}

class Clock {
 public:
  static auto init() -> void
  {
    clock_init();
  }
};

#endif
