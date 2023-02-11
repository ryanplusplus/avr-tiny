/*!
 * @file
 * @brief Dummy header for targets without a PB0 neopixel defined.
 */

#ifndef pb0_neopixel_h
#define pb0_neopixel_h

#include <stdint.h>

typedef struct
{
  uint8_t r;
  uint8_t g;
  uint8_t b;
} pb0_neopixel_color_t;

static inline void pb0_neopixel_init(void)
{
}

static inline void pb0_neopixel_write(const pb0_neopixel_color_t* data, uint16_t count)
{
  (void)data;
  (void)count;
}

static inline void pb0_neopixel_write_all(const pb0_neopixel_color_t* data, uint16_t count)
{
  (void)data;
  (void)count;
}

static inline void pb0_neopixel_reset(void)
{
}

#endif
