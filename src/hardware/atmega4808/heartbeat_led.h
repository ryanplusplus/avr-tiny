/*!
 * @file
 * @brief
 */

#ifndef heartbeat_led_h
#define heartbeat_led_h

#include <avr/io.h>

static inline void heartbeat_led_init(void)
{
  PORTC.OUTTGL = PIN2_bm;
}

static inline void heartbeat_led_toggle(void)
{
  PORTC.DIRSET = PIN2_bm;
}

#endif
