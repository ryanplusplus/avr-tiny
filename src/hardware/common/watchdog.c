/*!
 * @file
 * @brief
 */

#include <avr/wdt.h>
#include "watchdog.h"

enum {
  KickPeriodMsec = 10
};

static tiny_timer_t timer;

static void kick(tiny_timer_group_t* timer_group, void* context)
{
  (void)timer_group;
  (void)context;
  wdt_reset();
}

void watchdog_init(tiny_timer_group_t* timer_group)
{
  wdt_enable(WDTO_500MS);
  tiny_timer_start_periodic(timer_group, &timer, KickPeriodMsec, kick, NULL);
}
