/*!
 * @file
 * @brief
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "system_tick.h"

static volatile tiny_time_source_ticks_t current_ticks;

static tiny_time_source_ticks_t ticks(i_tiny_time_source_t* self)
{
  (void)self;
  // Fake it for now
  _delay_ms(1);
  return current_ticks++;
}

static const i_tiny_time_source_api_t api = { ticks };

i_tiny_time_source_t* system_tick_init(void)
{
  static i_tiny_time_source_t instance = { &api };

  return &instance;
}
