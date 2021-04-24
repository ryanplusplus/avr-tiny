/*!
 * @file
 * @brief
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stddef.h>
#include "usart0.h"
#include "tiny_single_subscriber_event.h"

static i_tiny_uart_t self;
static tiny_single_subscriber_event_t send_complete;
static tiny_single_subscriber_event_t receive;

ISR(USART_RX_vect)
{
  tiny_uart_on_receive_args_t args = { UDR0 };
  tiny_single_subscriber_event_publish(&receive, &args);
}

ISR(USART_TX_vect)
{
  tiny_single_subscriber_event_publish(&send_complete, NULL);
}

static void send(i_tiny_uart_t* self, uint8_t byte)
{
  (void)self;
  UDR0 = byte;
}

static i_tiny_event_t* on_send_complete(i_tiny_uart_t* self)
{
  (void)self;
  return &send_complete.interface;
}

static i_tiny_event_t* on_receive(i_tiny_uart_t* self)
{
  (void)self;
  return &receive.interface;
}

static const i_tiny_uart_api_t api = { send, on_send_complete, on_receive };

static inline void initialize_usart(uint16_t baud)
{
  // Enable RX, TX, and corresponding interrupts
  UCSR0B = _BV(RXCIE0) | _BV(TXCIE0) | _BV(RXEN0) | _BV(TXEN0);

  // Asynchronous mode, no parity, 1 stop bit, 8 data bits
  UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);

  // Set baud
  UBRR0H = (baud >> 8);
  UBRR0L = (baud & 0xFF);
}

i_tiny_uart_t* usart0_init(uint16_t baud)
{
  tiny_single_subscriber_event_init(&send_complete);
  tiny_single_subscriber_event_init(&receive);

  initialize_usart(baud);

  self.api = &api;
  return &self;
}
