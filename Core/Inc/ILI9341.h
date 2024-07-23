/*
 * ILI9341.h
 *
 *  Created on: Mar 15, 2024
 *      Author: moham
 */

#ifndef INC_ILI9341_H_
#define INC_ILI9341_H_
#include "stm32f1xx_hal.h"






uint8_t LCD_READ_RET(void);
void LCD_SEND_CMD(uint8_t cmd);
void LCD_WRITE_PARAM(uint8_t param);
/*
void LCD_CMD_SWRESET(void);
uint32_t LCD_CMD_RDDST(void);
uint8_t LCD_CMD_RDDPM(void);
uint8_t LCD_CMD_RDDCOLMOD(void);
void LCD_CMD_SLPOUT(void);
void LCD_CMD_DISPOFF(void);
void LCD_CMD_DISPON(void);
void LCD_CMD_WRDISBV(uint8_t value);
uint8_t LCD_CMD_RDDISBV();
void LCD_CMD_WRCTRLD(uint8_t value);
uint8_t LCD_CMD_RDCTRLD(void);

void LCD_CMD_VMCTRL1(uint8_t VMH, uint8_t VML);
*/
void LCD_CMD_RAMRD(uint8_t* buff);
void LCD_CMD_RAMWR(uint8_t* buff, int length);
void LCD_FILL(uint16_t color);
void LCD_FILL_AREA(uint16_t color, uint16_t width, uint16_t height, uint16_t origin_x, uint16_t origin_y);
void LCD_FILL_BUFFER_AREA(uint8_t* buffer, uint16_t width, uint16_t height, uint16_t origin_x, uint16_t origin_y);
void LCD_FILL_BUFFER_PART_START_AREA(uint8_t* buffer, uint16_t width, uint16_t height, uint16_t part, uint16_t origin_x, uint16_t origin_y);
void LCD_FILL_BUFFER_PART_CONTI_AREA(uint8_t* buffer, uint16_t part);
void LCD_INIT(void);


#endif /* INC_ILI9341_H_ */
