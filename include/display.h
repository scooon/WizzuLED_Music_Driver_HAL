#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef char byte;

#include "main.h"
#include "u8g2.h"

extern I2C_HandleTypeDef hi2c1;

#define DEVICE_ADDRESS 0x3C
#define TX_TIMEOUT 100




uint8_t u8x8_stm32_gpio_and_delay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
uint8_t u8x8_byte_stm32_hw_i2c(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);


void Display_Init(void);
void Display_String(byte x, byte y, char* content);
void Display_Brightness(byte intensity);


#ifdef __cplusplus
}
#endif

#endif