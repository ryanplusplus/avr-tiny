/*!
 * @file
 * @brief
 */

#include <stddef.h>
#include <avr/io.h>
#include "heartbeat.h"
#include "heartbeat_led.h"

enum {
  half_period_in_msec = 500
};

static tiny_timer_t timer;

static void blink(void* context)
{
  (void)context;
  heartbeat_led_toggle();
}

void heartbeat_init(tiny_timer_group_t* timer_group)
{
  heartbeat_led_init();
  heartbeat_led_toggle();
  tiny_timer_start_periodic(timer_group, &timer, half_period_in_msec, NULL, blink);
}
