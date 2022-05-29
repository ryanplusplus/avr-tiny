/*!
 * @file
 * @brief
 */

#ifndef usart0_h
#define usart0_h

#include <stdint.h>
#include <stdbool.h>
#include "hal/i_tiny_uart.h"

i_tiny_uart_t* usart0_init(bool u2x, uint16_t baud);

#endif
