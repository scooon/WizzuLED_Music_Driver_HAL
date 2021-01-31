#include "uart.h"

void send_char(char c)
{
	HAL_UART_Transmit(&uart, (uint8_t*)&c, 1, 1000);
}

int __io_putchar(int ch)
{
	if (ch == '\n')
		send_char('\r');
	send_char(ch);
	return ch;
}


void Uart_Init(){
  // UART
  __HAL_RCC_USART2_CLK_ENABLE();

  GPIO_InitTypeDef gpio;
  gpio.Mode = GPIO_MODE_AF_PP;
  gpio.Pin = GPIO_PIN_2;
  gpio.Pull = GPIO_NOPULL;
  gpio.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &gpio);

  gpio.Mode = GPIO_MODE_AF_INPUT;
  gpio.Pin = GPIO_PIN_3;
  HAL_GPIO_Init(GPIOA, &gpio);

  uart.Instance = USART2;
  uart.Init.BaudRate = 115200;
  uart.Init.WordLength = UART_WORDLENGTH_8B;
  uart.Init.Parity = UART_PARITY_NONE;
  uart.Init.StopBits = UART_STOPBITS_1;
  uart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  uart.Init.OverSampling = UART_OVERSAMPLING_16;
  uart.Init.Mode = UART_MODE_TX_RX;
  HAL_UART_Init(&uart);
}

void send_string(char *s)
{
  HAL_UART_Transmit(&uart, (uint8_t *)s, strlen(s), 1000);
}