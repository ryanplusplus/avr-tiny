/*!
 * @file
 * @brief
 */

#ifndef i_tiny_character_lcd_h
#define i_tiny_character_lcd_h

#include <stdint.h>

enum {
  tiny_character_lcd_command_clear = 0x01,

  tiny_character_lcd_command_return_home = 0x02,

  tiny_character_lcd_command_move_cursor_left = 0x04,
  tiny_character_lcd_command_move_cursor_right = 0x06,

  tiny_character_lcd_command_move_cursor_to_first_line_home = 0x80,
  tiny_character_lcd_command_move_cursor_to_second_line_home = 0xC0,

  tiny_character_lcd_command_shift_display_right = 0x05,
  tiny_character_lcd_command_shift_display_left = 0x07,

  tiny_character_lcd_command_display_off = 0x08,
  tiny_character_lcd_command_display_on_cursor_off = 0x0c,
  tiny_character_lcd_command_display_on_cursor_on = 0x0e,
  tiny_character_lcd_command_display_on_cursor_blinking = 0x0f
};

struct i_tiny_character_lcd_api_t;

typedef struct {
  const struct i_tiny_character_lcd_api_t* api;
} i_tiny_character_lcd_t;

typedef struct i_tiny_character_lcd_api_t {
  void (*send_command)(
    i_tiny_character_lcd_t* self,
    uint8_t command);

  void (*write_string)(
    i_tiny_character_lcd_t* self,
    const char* string);
} i_tiny_character_lcd_api_t;

#define tiny_character_lcd_send_command(self, command) \
  (self)->api->send_command((self), (command))

#define tiny_character_lcd_write_string(self, string) \
  (self)->api->write_string((self), (string))

#endif
