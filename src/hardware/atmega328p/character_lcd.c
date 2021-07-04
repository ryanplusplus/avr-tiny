/*!
 * @file
 * @brief
 */

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stddef.h>
#include "character_lcd.h"

#define ddr DDRD
#define port PORTD

enum {
  command_8_bit_mode = 0x33,
  command_4_bit_mode = 0x32
};

enum {
  data = 0x0F,
  rs = 1 << 5,
  en = 1 << 4
};

static void send_nybble(uint8_t nybble)
{
  port &= ~(data | en);
  port |= nybble | en;
  port &= ~en;
  _delay_us(50);
}

static void send_byte(uint8_t byte)
{
  send_nybble(byte >> 4);
  send_nybble(byte & 0x0F);
}

static void send_data(uint8_t data)
{
  port |= rs;
  send_byte(data);
}

static void send_command(
  i_tiny_character_lcd_t* self,
  uint8_t command)
{
  (void)self;

  port &= ~rs;
  send_byte(command);

  switch(command) {
    case tiny_character_lcd_command_clear:
    case tiny_character_lcd_command_return_home:
      _delay_ms(2);
      break;
  }
}

static void write_string(
  i_tiny_character_lcd_t* self,
  const char* string)
{
  (void)self;
  size_t length = strlen(string);

  for(size_t i = 0; i < length; i++) {
    send_data(string[i]);
  }
}

static const i_tiny_character_lcd_api_t api = { send_command, write_string };

i_tiny_character_lcd_t* character_lcd_init(void)
{
  static i_tiny_character_lcd_t self = { .api = &api };

  ddr |= (data | en | rs);

  send_command(NULL, command_8_bit_mode);
  send_command(NULL, command_4_bit_mode);
  send_command(NULL, tiny_character_lcd_command_display_on_cursor_off);
  send_command(NULL, tiny_character_lcd_command_clear);

  return &self;
}
