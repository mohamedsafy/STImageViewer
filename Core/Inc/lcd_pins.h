/*
 * lcd_pins.h
 *
 *  Created on: Apr 16, 2024
 *      Author: mohamed
 */

#ifndef INC_LCD_PINS_H_
#define INC_LCD_PINS_H_

// Pin Configurations

#define LCD_DATA_PORT GPIOB
#define LCD_D0_Pin_Number 8
#define LCD_D0_Pin GPIO_PIN_8
#define LCD_D1_Pin GPIO_PIN_9
#define LCD_D2_Pin GPIO_PIN_10
#define LCD_D3_Pin GPIO_PIN_11
#define LCD_D4_Pin GPIO_PIN_12
#define LCD_D5_Pin GPIO_PIN_13
#define LCD_D6_Pin GPIO_PIN_14
#define LCD_D7_Pin GPIO_PIN_15


#define LCD_RD_Pin GPIO_PIN_0
#define LCD_RD_GPIO_Port GPIOA
#define LCD_WR_Pin GPIO_PIN_1
#define LCD_WR_GPIO_Port GPIOA
#define LCD_RS_Pin GPIO_PIN_2
#define LCD_RS_GPIO_Port GPIOA
#define LCD_CS_Pin GPIO_PIN_3
#define LCD_CS_GPIO_Port GPIOA
#define LCD_RST_Pin GPIO_PIN_4
#define LCD_RST_GPIO_Port GPIOA


#define CS_SET LCD_CS_GPIO_Port->BSRR = LCD_CS_Pin
#define CS_RESET LCD_CS_GPIO_Port->BRR = LCD_CS_Pin

#define RS_SET LCD_RS_GPIO_Port->BSRR = LCD_RS_Pin
#define RS_RESET LCD_RS_GPIO_Port->BRR = LCD_RS_Pin

#define WR_SET LCD_WR_GPIO_Port->BSRR = LCD_WR_Pin
#define WR_RESET LCD_WR_GPIO_Port->BRR = LCD_WR_Pin

#define RD_SET LCD_RD_GPIO_Port->BSRR = LCD_RD_Pin
#define RD_RESET LCD_RD_GPIO_Port->BRR = LCD_RD_Pin

#define RST_SET LCD_RST_GPIO_Port->BSRR = LCD_RST_Pin
#define RST_RESET LCD_RST_GPIO_Port->BRR = LCD_RST_Pin

#define DATAOUT(n) LCD_DATA_PORT->ODR = (n<<LCD_D0_Pin_Number)
#define DATAIN LCD_DATA_PORT->IDR>>LCD_D0_Pin_Number


#define YP LCD_CS_Pin
#define YP_PORT LCD_CS_GPIO_Port

#define XM LCD_RS_Pin
#define XM_PORT LCD_RS_GPIO_Port

#define YM LCD_D1_Pin
#define YM_PORT LCD_DATA_PORT

#define XP LCD_D0_Pin
#define XP_PORT LCD_DATA_PORT

#include "gpio.h"

void Config_Control_Pins();
void Switch_Read(uint16_t pins, GPIO_TypeDef* port);
void Switch_Write(uint16_t pins, GPIO_TypeDef* port);
void Switch_Analog(uint16_t pins, GPIO_TypeDef* port);

#endif /* INC_LCD_PINS_H_ */
