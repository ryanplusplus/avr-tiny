/*!
 * @file
 * @brief 1 KHz tick at 8 MHz clock.
 */

#ifndef system_tick_h
#define system_tick_h

#include "i_tiny_time_source.h"

i_tiny_time_source_t* system_tick_init(void);

#endif
