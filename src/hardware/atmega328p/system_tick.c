/*!
 * @file
 * @brief
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "system_tick.h"

static volatile tiny_time_source_ticks_t current_ticks;

ISR(TIMER0_COMPA_vect)
{
  current_ticks++;
}

static tiny_time_source_ticks_t ticks(i_tiny_time_source_t* self)
{
  (void)self;

  tiny_time_source_ticks_t previous;
  tiny_time_source_ticks_t current = current_ticks;

  do {
    previous = current;
    current = current_ticks;
  } while(current != previous);

  return current;
}

static const i_tiny_time_source_api_t api = { ticks };

i_tiny_time_source_t* system_tick_init(void)
{
  static i_tiny_time_source_t instance = { &api };

  // Enable TIMER 0 clock
  PRR &= ~_BV(PRTIM0);

  // Clear timer on compare match
  TCCR0A = _BV(WGM01);

  // Prescalar 64
  // Count 125
  // 8 MHz / 64 / 125 == 1000 Hz
  TCCR0B = _BV(CS01) | _BV(CS00);
  OCR0A = 125;

  // Enable compare match A interrupt
  TIMSK0 = _BV(OCIE0A);

  return &instance;
}
