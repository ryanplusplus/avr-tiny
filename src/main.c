/*!
 * @file
 * @brief
 */

#include <stddef.h>
#include <avr/interrupt.h>
#include "timer0_system_tick.h"
#include "pb5_heartbeat.h"
#include "tiny_timer.h"
#include "watchdog.h"

static tiny_timer_group_t timer_group;
static tiny_timer_t timer;

static void kick_watchdog(tiny_timer_group_t* timer_group, void* context)
{
  (void)context;
  watchdog_kick();
  tiny_timer_start(timer_group, &timer, 50, kick_watchdog, NULL);
}

int main(void)
{
  cli();
  {
    watchdog_init(WDTO_250MS);
    tiny_timer_group_init(&timer_group, timer0_system_tick_init());
    pb5_heartbeat_init(&timer_group);
  }
  sei();

  kick_watchdog(&timer_group, NULL);

  while(true) {
    tiny_timer_group_run(&timer_group);
  }
}
