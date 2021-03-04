/*!
 * @file
 * @brief
 */

#include <stddef.h>
#include <avr/interrupt.h>
#include "system_tick.h"
#include "heartbeat.h"
#include "tiny_timer.h"
#include "watchdog.h"
#include "clock.h"

int main(void)
{
  static tiny_timer_group_t timer_group;

  cli();
  {
    clock_init();
    tiny_timer_group_init(&timer_group, system_tick_init());
    watchdog_init(&timer_group);
    heartbeat_init(&timer_group);
  }
  sei();

  while(true) {
    tiny_timer_group_run(&timer_group);
  }
}
