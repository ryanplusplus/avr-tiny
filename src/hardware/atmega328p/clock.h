/*!
 * @file
 * @brief
 */

#ifndef clock_h
#define clock_h

#include <avr/io.h>

static inline void clock_init(void)
{
  // Gate peripheral clocks
  PRR = 0;
}

#endif
