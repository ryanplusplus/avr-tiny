/*!
 * @file
 * @brief
 */

#ifndef watchdog_h
#define watchdog_h

#include <stdint.h>
#include <avr/wdt.h>
#include "tiny_timer.h"

void watchdog_init(tiny_timer_group_t* timer_group, uint8_t timeout);

#endif
