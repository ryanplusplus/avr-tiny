/*!
 * @file
 * @brief
 */

#include <avr/io.h>
#include "spi.h"

#define SPI_DDR DDRB
#define SS PINB2
#define MOSI PINB3
#define MISO PINB4
#define SCK PINB5

static void transfer(
  i_tiny_spi_t* self,
  const uint8_t* write_buffer,
  uint8_t* read_buffer,
  uint16_t buffer_size) {
  for(uint16_t i = 0; i < buffer_size; i++) {
    SPDR = write_buffer ? write_buffer[i] : 0x00;
    loop_until_bit_is_set(SPSR, SPIF);
    if(read_buffer) read_buffer[i] = SPDR;
  }
}

static const i_tiny_spi_api_t api = { transfer };

i_tiny_spi_t* spi_init(
  uint8_t cpol,
  uint8_t cpha,
  bool msb_first,
  spi_baud_t baud) {
  // Set SS, MOSI, and SCK as outputs
  // SS must be configured as an output to make sure that
  // the SPI peripheral doesn't switch to slave mode
  SPI_DDR |= _bv(SS) | _bv(MOSI) | _bv(SCK);

  // Enable SPI in master mode, set CPOL and CPHA, set bit
  // order, and set SPR0/1 to (partially) configure SCK
  // frequency
  SPCR = _bv(SPE) | _bv(MSTR) | (cpol << CPOL) | (cpha << CPHA) | (!msb_first << DORD) | (baud & 0x03);

  // Set SPI2X based on the configured baud to finish
  // configuring SCK frequency
  SPSR = baud >> 2;

  static i_tiny_spi_t self;
  self.api = &api;
  return &self;
}
