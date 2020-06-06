#include "uart.h"

extern char buffer[UART_BUFFER_SIZE];
volatile uint8_t buffer_index = 0;
volatile UART_Type *uartAttachedToBuffer;

