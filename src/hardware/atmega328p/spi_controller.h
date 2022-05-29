/*!
 * @file
 * @brief
 */

#ifndef spi_controller_h
#define spi_controller_h

#include <stdint.h>
#include <stdbool.h>
#include "hal/i_tiny_spi.h"

// Baud rate settings assume 8 MHz clock
enum {
  spi_baud_4mhz = 4,
  spi_baud_2mhz = 0,
  spi_baud_1mhz = 5,
  spi_baud_500khz = 1,
  spi_baud_250khz = 6,
  spi_baud_125khz = 2,
  spi_baud_62500hz = 3
};
typedef uint8_t spi_baud_t;

i_tiny_spi_t* spi_controller_init(
  uint8_t cpol,
  uint8_t cpha,
  bool msb_first,
  spi_baud_t baud);

#endif
