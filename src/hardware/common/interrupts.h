/*!
 * @file
 * @brief
 */

#ifndef interrupts_h
#define interrupts_h

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>

static inline void interrupts_disable(void)
{
  cli();
}

static inline void interrupts_enable(void)
{
  sei();
}

static inline void interrupts_wait_for_interrupt(void)
{
#if defined(__AVR_ATmega328P__)
  SMCR = _BV(SE);
  __asm__ __volatile__("sleep");
#elif defined(__AVR_ATtiny85__) || defined(__AVR_ATtiny88__)
  MCUCR &= ~(_BV(SM0) | _BV(SM1));
  MCUCR |= _BV(SE);
  __asm__ __volatile__("sleep");
#endif
}

static inline uint8_t interrupts_save(void)
{
  uint8_t state = SREG;
  interrupts_disable();
  return state;
}

static inline void interrupts_restore(uint8_t state)
{
  SREG = state;
}

#define interrupts_critical_section(...) \
  do {                                   \
    uint8_t state = interrupts_save();   \
    __VA_ARGS__                          \
    interrupts_restore(state);           \
  } while(0)

#endif
