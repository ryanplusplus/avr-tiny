/*!
 * @file
 * @brief
 */

#include "watchdog.h"

void watchdog_init(uint8_t timeout)
{
  wdt_disable();
  wdt_enable(timeout);
}

void watchdog_kick(void)
{
  wdt_reset();
}
