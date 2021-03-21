/*!
 * @file
 * @brief
 */

#ifndef heartbeat_led_h
#define heartbeat_led_h

#include <avr/io.h>

static inline void heartbeat_led_init(void)
{
  DDRB |= _BV(5);
}

static inline void heartbeat_led_toggle(void)
{
  PINB |= _BV(5);
}

#endif
