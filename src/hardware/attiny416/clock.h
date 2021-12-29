/*!
 * @file
 * @brief
 */

#ifndef clock_h
#define clock_h

#include <avr/io.h>

/*!
 * Removes the default prescalar (6) to run at 20 MHz (default) or 16 MHz
 * (settable via fuse)
 */
static inline void clock_init(void)
{
  // Unlock writes to protected I/O registers
  CCP = CCP_IOREG_gc;

  // Disable the prescalar
  CLKCTRL.MCLKCTRLB &= ~CLKCTRL_PEN_bm;
}

#endif
