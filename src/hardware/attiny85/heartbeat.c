/*!
 * @file
 * @brief
 */

#include <stddef.h>
#include <avr/io.h>
#include "heartbeat.h"

enum {
  half_period_in_msec = 500,
  pin_1 = _BV(1)
};

static tiny_timer_t timer;

static void blink(tiny_timer_group_t* group, void* context)
{
  (void)group;
  (void)context;
  PINB |= pin_1;
}

void heartbeat_init(tiny_timer_group_t* timer_group)
{
  DDRB |= pin_1;
  tiny_timer_start_periodic(timer_group, &timer, half_period_in_msec, blink, NULL);
}
