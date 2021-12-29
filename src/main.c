/*!
 * @file
 * @brief
 */

#include "interrupts.h"
#include "system_tick.h"
#include "heartbeat.h"
#include "tiny_timer.h"
#include "watchdog.h"
#include "clock.h"

int main(void)
{
  static tiny_timer_group_t timer_group;

  interrupts_disable();
  {
    clock_init();
    tiny_timer_group_init(&timer_group, system_tick_init());
    watchdog_init(&timer_group);
    heartbeat_init(&timer_group);
  }
  interrupts_enable();

  while(1) {
    tiny_timer_group_run(&timer_group);
  }
}
