/*!
 * @file
 * @brief
 */

#include <stddef.h>
#include <avr/io.h>
#include "pb5_heartbeat.h"

enum {
  half_period_in_msec = 500,
  pin_5 = (1 << 5)
};

static tiny_timer_t timer;

static void blink(tiny_timer_group_t* group, void* context)
{
  (void)group;
  (void)context;
  PINB |= pin_5;
}

void pb5_heartbeat_init(tiny_timer_group_t* timer_group)
{
  DDRB |= pin_5;
  tiny_timer_start_periodic(timer_group, &timer, half_period_in_msec, blink, NULL);
}
