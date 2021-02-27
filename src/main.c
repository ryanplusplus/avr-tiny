/*!
 * @file
 * @brief
 */

#include <stddef.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#ifdef __AVR_DEV_LIB_NAME__
#endif

void main(void) {
  PORTF.DIRSET = PIN5_bm;

  while(1) {
    PORTF.OUTCLR = PIN5_bm;
    _delay_ms(500);

    PORTF.OUTSET = PIN5_bm;
    _delay_ms(100);
  }
}
