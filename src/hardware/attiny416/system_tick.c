/*!
 * @file
 * @brief
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "system_tick.h"
#include "heartbeat_led.h"

static volatile tiny_time_source_ticks_t current_ticks;

ISR(TCB0_INT_vect)
{
  TCB0.INTFLAGS = TCB_CAPT_bm;
  current_ticks++;

  if(current_ticks % 100 == 0) {
    heartbeat_led_toggle();
  }
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

  // TCB0.CTRLB defaults to periodic interrupt mode

  // Set interrupt frequency to 1 KHz
  TCB0.CCMP = F_CPU / 1000;

  // Enable the interrupt
  TCB0.INTCTRL |= TCB_CAPT_bm;

  // Enable TCB0
  TCB0.CTRLA |= TCB_ENABLE_bm;

  return &instance;
}
