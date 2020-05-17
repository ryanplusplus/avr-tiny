/*!
 * @file
 * @brief Standard mode (100 KHz) @ 8 MHz CPU clock
 */

#ifndef twi_h
#define twi_h

#include <hal/i_tiny_i2c.h>

i_tiny_i2c_t* twi_init(void);

#endif
