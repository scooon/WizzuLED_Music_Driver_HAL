#include "display.h"

static u8g2_t u8g2;



uint8_t u8x8_stm32_gpio_and_delay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
  /* STM32 supports HW SPI, Remove unused cases like U8X8_MSG_DELAY_XXX & U8X8_MSG_GPIO_XXX */
  switch (msg)
  {
  case U8X8_MSG_GPIO_AND_DELAY_INIT:
    /* Insert codes for initialization */
    break;
  case U8X8_MSG_DELAY_MILLI:
    /* ms Delay */
    HAL_Delay(arg_int);
    break;
  case U8X8_MSG_GPIO_CS:
    /* Insert codes for SS pin control */
    //HAL_GPIO_WritePin(OLED_CS_GPIO_Port, OLED_CS_Pin, arg_int);
    break;
  case U8X8_MSG_GPIO_DC:
    /* Insert codes for DC pin control */
    //HAL_GPIO_WritePin(OLED_DC_GPIO_Port, OLED_DC_Pin, arg_int);
    break;
  case U8X8_MSG_GPIO_RESET:
    /* Insert codes for RST pin control */
    //HAL_GPIO_WritePin(OLED_RST_GPIO_Port, OLED_RST_Pin, arg_int);
    break;
  }
  return 1;
}

uint8_t u8x8_byte_stm32_hw_i2c(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
  /* u8g2/u8x8 will never send more than 32 bytes between START_TRANSFER and END_TRANSFER */
  static uint8_t buffer[32];
  static uint8_t buf_idx;
  uint8_t *data;

  switch (msg)
  {
  case U8X8_MSG_BYTE_SEND:
    data = (uint8_t *)arg_ptr;
    while (arg_int > 0)
    {
      buffer[buf_idx++] = *data;
      data++;
      arg_int--;
    }
    break;
  case U8X8_MSG_BYTE_INIT:
    /* add your custom code to init i2c subsystem */
    break;
  case U8X8_MSG_BYTE_SET_DC:
    break;
  case U8X8_MSG_BYTE_START_TRANSFER:
    buf_idx = 0;
    break;
  case U8X8_MSG_BYTE_END_TRANSFER:
    if (HAL_I2C_Master_Transmit(&hi2c1, (DEVICE_ADDRESS << 1), buffer, buf_idx, TX_TIMEOUT) != HAL_OK)
      return 0;
    break;
  default:
    return 0;
  }
  return 1;
}

void Display_Init(void)
{
 /* I2C Interface */
  u8g2_Setup_sh1106_i2c_128x64_noname_f(&u8g2, U8G2_R0, u8x8_byte_stm32_hw_i2c, u8x8_stm32_gpio_and_delay);

  /* Initialize Display */
  u8g2_InitDisplay(&u8g2);
  u8g2_SetPowerSave(&u8g2, 0);
}

void Display_String(byte x, byte y, char* content)
{
     
  u8g2_SetFont(&u8g2, u8g2_font_5x7_tr);
  u8g2_DrawStr(&u8g2, x, y, content);
  u8g2_SendBuffer(&u8g2);

}

void Display_Brightness(byte intensity){
    u8g2_SetContrast(&u8g2, intensity);
}