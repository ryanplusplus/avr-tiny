/*!
 * @file
 * @brief
 */

#include <avr/interrupt.h>
#include "Clock.hpp"
#include "SystemTick.hpp"
#include "Watchdog.hpp"
#include "Heartbeat.hpp"
#include "tiny/Timer.h"

using namespace tiny;

int main(void)
{
  cli();

  Clock::init();
  SystemTick system_tick{};
  TimerGroup timer_group{ system_tick };
  Watchdog watchdog{ timer_group };
  Heartbeat heartbeat{ timer_group };

  sei();

  while(1) {
    timer_group.run();
  }
}
