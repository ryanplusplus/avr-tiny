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
#include "pb0_neopixel.h"
#include "tiny_utils.h"

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

  pb0_neopixel_init();

  interrupts_critical_section({
    pb0_neopixel_color_t color = { 0, 9, 2 };

    for(uint8_t i = 0; i < 8; i++) {
      pb0_neopixel_write(&color, 1);
      color.r -= 1;
      color.b += 1;
    }
  });

  while(1) {
    if(tiny_timer_group_run(&timer_group)) {
      interrupts_wait_for_interrupt();
    }
  }
}
