/*!
 * @file
 * @brief
 */

#ifndef Interrupts_hpp
#define Interrupts_hpp

extern "C" {
#include "interrupts.h"
}

class Interrupts {
 public:
  static auto enable() -> void
  {
    interrupts_enable();
  }

  static auto disable() -> void
  {
    interrupts_disable();
  }

  static auto wait_for_interrupt() -> void
  {
    interrupts_wait_for_interrupt();
  }
};

#endif
