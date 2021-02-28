/*!
 * @file
 * @brief
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "system_tick.h"

static volatile tiny_time_source_ticks_t current_ticks;

ISR(TIMER1_COMPA_vect)
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

  // Clear on compare match
  // Prescalar 8192
  TCCR1 |= _BV(CTC1) | _BV(CS10) | _BV(CS11) | _BV(CS12);

  // Compare match 122 (8000000 / 64 / 125 == 1000 Hz)
  OCR1C = 125;

  // Enable compare match interrupt
  TIMSK |= _BV(OCIE1A);

  return &instance;
}
