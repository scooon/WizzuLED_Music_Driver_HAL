#ifndef __UART_H__
#define __UART_H__

#ifdef __cplusplus
extern "C" {
#endif


#include "main.h"


UART_HandleTypeDef uart;


void send_char(char c);
int __io_putchar(int ch);
void Uart_Init();
void send_string(char *s);

#ifdef __cplusplus
}
#endif

#endif