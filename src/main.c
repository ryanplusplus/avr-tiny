/*!
 * @file
 * @brief
 */

#include <avr/io.h>
#include <util/delay.h>

int main(void) {
  DDRB |= _BV(5);

  while(1) {
    PORTB |= _BV(5);
    _delay_ms(500);

    PORTB &= ~_BV(5);
    _delay_ms(500);
  }

  return 0;
}
