/*!
 * @file
 * @brief
 */

#ifndef heartbeat_led_h
#define heartbeat_led_h

#include <avr/io.h>

static inline void heartbeat_led_init(void)
{
  DDRD |= _BV(0);
}

static inline void heartbeat_led_toggle(void)
{
  PIND |= _BV(0);
}

#endif
