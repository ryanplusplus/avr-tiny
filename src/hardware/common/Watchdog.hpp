/*!
 * @file
 * @brief
 */

#ifndef Watchdog_hpp
#define Watchdog_hpp

#include <avr/wdt.h>
#include "tiny/Timer.h"

class Watchdog {
 public:
  Watchdog(tiny::TimerGroup& timer_group)
    : timer()
  {
    wdt_enable(WDTO_500MS);

    timer_group.start_periodic(
      this->timer, period, (void*)nullptr, +[](void* context) {
        (void)context;
        wdt_reset();
      });
  }

 private:
  static const tiny::TimerTicks period = 10;
  tiny::Timer timer;
};

#endif
