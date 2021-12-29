/*!
 * @file
 * @brief
 */

#ifndef usart0_h
#define usart0_h

#include <stdint.h>
#include "hal/i_tiny_uart.h"

i_tiny_uart_t* usart0_init(uint16_t baud);

#endif
