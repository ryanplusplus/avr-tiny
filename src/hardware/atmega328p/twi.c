/*!
 * @file
 * @brief
 */

#include <stddef.h>
#include <avr/io.h>
#include "twi.h"
#include "tiny_utils.h"

enum {
  write_bit = 0,
  read_bit = 1,

  status_start_transmitted = 0x08,
  status_restart_transmitted = 0x10,
  status_write_address_acked = 0x18,
  status_read_address_acked = 0x40,
  status_write_byte_acked = 0x28,
  status_read_byte_acked = 0x50,
  status_read_byte_nacked = 0x58
};

static inline uint8_t status(void)
{
  return TWSR & 0xFC;
}

#define assert_status(expected) \
  do {                          \
    if(status() != expected) {  \
      reset(NULL);              \
      return false;             \
    }                           \
  } while(0)

#define assert_status_or(expected, alternative)         \
  do {                                                  \
    uint8_t _status = status();                         \
    if(_status != expected && _status != alternative) { \
      reset(NULL);                                      \
      return false;                                     \
    }                                                   \
  } while(0)

static inline void wait_for_complete(void)
{
  loop_until_bit_is_set(TWCR, TWINT);
}

static inline void start(void)
{
  TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWSTA);
  wait_for_complete();
}

static inline void stop(void)
{
  TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWSTO);
}

static inline uint8_t read_byte_ack(void)
{
  TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWEA);
  wait_for_complete();
  return TWDR;
}

static inline uint8_t read_byte_nack(void)
{
  TWCR = _BV(TWINT) | _BV(TWEN);
  wait_for_complete();
  return TWDR;
}

static inline void write_byte(uint8_t byte)
{
  TWDR = byte;
  TWCR = _BV(TWINT) | _BV(TWEN);
  wait_for_complete();
}

static void reset(i_tiny_i2c_t* self)
{
  (void)self;

  // Disable peripheral
  TWCR &= ~_BV(TWEN);

  // 8 MHz / (16 + 2 * TWBR=32 * Prescalar=1) => ~100 KHz
  // Prescalar defaults to 1 in TWSR
  TWBR = 32;

  // Enable peripheral
  TWCR |= _BV(TWEN);
}

static bool write(
  i_tiny_i2c_t* self,
  uint8_t address,
  bool prepare_for_restart,
  const void* _buffer,
  uint16_t buffer_size)
{
  reinterpret(buffer, _buffer, const uint8_t*);
  (void)self;

  start();
  assert_status_or(status_start_transmitted, status_restart_transmitted);

  write_byte((address << 1) | write_bit);
  assert_status(status_write_address_acked);

  for(uint16_t i = 0; i < buffer_size; i++) {
    write_byte(buffer[i]);
    assert_status(status_write_byte_acked);
  }

  if(!prepare_for_restart) {
    stop();
  }

  return true;
}

static bool read(
  i_tiny_i2c_t* self,
  uint8_t address,
  bool prepare_for_restart,
  void* _buffer,
  uint16_t buffer_size)
{
  reinterpret(buffer, _buffer, uint8_t*);
  (void)self;

  start();
  assert_status_or(status_start_transmitted, status_restart_transmitted);

  write_byte((address << 1) | read_bit);
  assert_status(status_read_address_acked);

  for(uint16_t i = 0; i < buffer_size; i++) {
    if(i + 1 < buffer_size) {
      buffer[i] = read_byte_ack();
      assert_status(status_read_byte_acked);
    }
    else {
      buffer[i] = read_byte_nack();
      assert_status(status_read_byte_nacked);
    }
  }

  if(!prepare_for_restart) {
    stop();
  }

  return true;
}

static const i_tiny_i2c_api_t api = { write, read, reset };

i_tiny_i2c_t* twi_init(void)
{
  // Enable TWI clock
  PRR &= ~_BV(PRTWI);

  reset(NULL);

  static i_tiny_i2c_t self;
  self.api = &api;
  return &self;
}
