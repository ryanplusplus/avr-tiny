/*!
 * @file
 * @brief
 */

#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include "system_tick.h"
#include "heartbeat.h"
#include "tiny_timer.h"
#include "watchdog.h"
#include "clock.h"

#define lcd_ddr DDRD
#define lcd_port PORTD

enum {
  data = 0x0F,
  rs = 1 << 5,
  en = 1 << 4
};

enum {
  command_8_bit_mode = 0x33,
  command_4_bit_mode = 0x32,
  command_display_on_cursor_off = 0x0C,
  command_clear = 0x01
};

static void send_nybble(uint8_t nybble)
{
  lcd_port &= ~(data | en);
  lcd_port |= nybble | en;
  lcd_port &= ~en;
  _delay_ms(2);
}

static void send_byte(uint8_t byte)
{
  send_nybble(byte >> 4);
  send_nybble(byte & 0x0F);
}

static void send_data(uint8_t data)
{
  lcd_port |= rs;
  send_byte(data);
}

static void send_string(const char* data)
{
  size_t length = strlen(data);

  for(size_t i = 0; i < length; i++) {
    send_data(data[i]);
  }
}

static void send_command(uint8_t command)
{
  lcd_port &= ~rs;
  send_byte(command);
}

int main(void)
{
  static tiny_timer_group_t timer_group;

  cli();
  {
    clock_init();
    tiny_timer_group_init(&timer_group, system_tick_init());
    watchdog_init(&timer_group);
    heartbeat_init(&timer_group);
  }
  sei();

  lcd_ddr |= (data | en | rs);

  send_command(command_8_bit_mode);
  send_command(command_4_bit_mode);
  send_command(command_display_on_cursor_off);
  send_command(command_clear);

  send_string("Hello, World!");

  while(1) {
    tiny_timer_group_run(&timer_group);
  }
}
