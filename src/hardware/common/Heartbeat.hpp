/*!
 * @file
 * @brief
 */

#ifndef Heartbeat_hpp
#define Heartbeat_hpp

#include "tiny/Timer.h"

extern "C" {
#include "heartbeat_led.h"
}

class Heartbeat {
 public:
  Heartbeat(tiny::TimerGroup& timer_group)
    : timer()
  {
    heartbeat_led_init();

    timer_group.start_periodic(
      this->timer, period, (void*)nullptr, +[](void* context, tiny::TimerGroup& timer_group) {
        (void)context;
        (void)timer_group;
        heartbeat_led_toggle();
      });
  }

 private:
  static const tiny::TimerTicks period = 500;
  tiny::Timer timer;
};

#endif
