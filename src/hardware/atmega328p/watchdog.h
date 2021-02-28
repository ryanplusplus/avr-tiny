/*!
 * @file
 * @brief
 */

#ifndef watchdog_h
#define watchdog_h

#include <stdint.h>
#include <avr/wdt.h>

void watchdog_init(uint8_t timeout);
void watchdog_kick(void);

#endif
