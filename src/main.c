/*!
 * @file
 * @brief
 */

#include "interrupts.h"
#include "system_tick.h"
#include "heartbeat.h"
#include "tiny_timer.h"
#include "watchdog.h"
#include "clock.h"

#include "character_lcd.h"

int main(void)
{
  static tiny_timer_group_t timer_group;

  interrupts_disable();
  {
    clock_init();
    tiny_timer_group_init(&timer_group, system_tick_init());
    watchdog_init(&timer_group);
    heartbeat_init(&timer_group);
  }
  interrupts_enable();

  i_tiny_character_lcd_t* lcd = character_lcd_init();
  tiny_character_lcd_write_string(lcd, "Hello, World!");
  tiny_character_lcd_send_command(lcd, tiny_character_lcd_command_move_cursor_to_second_line_home);
  tiny_character_lcd_write_string(lcd, "Goodbye, World!");

  while(1) {
    tiny_timer_group_run(&timer_group);
  }
}
