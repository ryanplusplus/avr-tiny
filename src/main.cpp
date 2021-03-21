/*!
 * @file
 * @brief
 */

extern "C" {
#include <stddef.h>
#include <avr/interrupt.h>
#include "clock.h"
}

#include "SystemTick.hpp"
#include "Watchdog.hpp"
#include "Heartbeat.hpp"
#include "tiny/Timer.h"

using namespace tiny;

int main(void)
{
  cli();

  clock_init();
  SystemTick system_tick{};
  TimerGroup timer_group{ system_tick };
  Watchdog watchdog{ timer_group };
  Heartbeat heartbeat{ timer_group };

  sei();

  while(true) {
    timer_group.run();
  }
}
