/*!
 * @file
 * @brief
 */

#ifndef heartbeat_led_h
#define heartbeat_led_h

#include <avr/io.h>

static inline void heartbeat_led_init(void)
{
  PORTB.OUTTGL = PIN5_bm;
}

static inline void heartbeat_led_toggle(void)
{
  PORTB.DIRSET = PIN5_bm;
}

#endif
