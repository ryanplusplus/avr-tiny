/*!
 * @file
 * @brief
 */

#include <avr/io.h>
#include "interrupts.h"

#ifndef neopixel_port
#error "neopixel_port must be defined"
#endif

#ifndef neopixel_pin
#error "neopixel_pin must be defined"
#endif

#define port_register neopixel_concat(PORT, neopixel_port)

static void send_byte(uint8_t byte)
{
#if F_CPU == 8000000UL
  __asm__ __volatile__(
    "_send_byte:\n"
    "  ldi r16,8\n"
    "\n"
    "send_bit:\n"
    "  sbi %[port], %[port_bit]\n"
    "  lsl %[byte]\n"
    "  brcs send_1\n"
    "\n"
    "send_0:\n"
    "  cbi %[port], %[port_bit]\n"
    "  nop\n"
    "  nop\n"
    "  dec r16\n"
    "  brne send_bit\n"
    "  rjmp done$\n"
    "\n"
    "send_1:\n"
    "  nop\n"
    "  dec r16\n"
    "  cbi %[port], %[port_bit]\n"
    "  brne send_bit\n"
    "\n"
    "done:\n"
    :
    : [byte] "r"(byte), [port] "M"(_SFR_IO_ADDR(port_register)), [port_bit] "M"(neopixel_pin)
    : "r16", "memory");
#else
#error "Unsupported F_CPU"
#endif
}

void neopixel_concat(neopixel_api_name, _init)(void)
{
  neopixel_concat(DDR, neopixel_port) |= _BV(neopixel_pin);
}

void neopixel_concat(neopixel_api_name, _write)(const neopixel_concat(neopixel_api_name, _color_t) * data, uint16_t count)
{
  interrupts_critical_section({
    for(uint16_t i = 0; i < count; i++) {
      for(uint8_t j = 0; j < sizeof(data[0]); j++) {
        send_byte(((const uint8_t*)data)[i * sizeof(data[0]) + j]);
      }
    }
  });
}

void neopixel_concat(neopixel_api_name, _write_all)(const neopixel_concat(neopixel_api_name, _color_t) * data, uint16_t count)
{
  interrupts_critical_section({
    for(uint16_t i = 0; i < count; i++) {
      for(uint8_t j = 0; j < sizeof(data[0]); j++) {
        send_byte(((const uint8_t*)data)[j]);
      }
    }
  });
}

void neopixel_concat(neopixel_api_name, _reset)(void)
{
  // 50 usec is required for reset

#if F_CPU == 8000000UL
  // 50 usec == 400 cycles @ 8 MHz
  __asm__ __volatile__(
    "reset_neopixel:\n"
    "	 ldi r16, 100\n" // 1 cycle
    "loop:\n"
    "	 dec r16\n" // 1 cycle
    "	 brne loop\n" // 2 cycles (if it branches)
    :
    :
    : "r16");
#else
#error "Unsupported F_CPU"
#endif
}
