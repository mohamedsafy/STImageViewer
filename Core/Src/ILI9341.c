/*
 * ILI9341.c
 *
 *  Created on: Mar 15, 2024
 *      Author: moham
 */
#include "ILI9341.h"
#include "lcd_pins.h"


void LCD_RESET(void)
{
	RST_RESET;
	HAL_Delay(100);
	RST_SET;
	HAL_Delay(50);
}

void LCD_SEND_CMD(uint8_t cmd){
	Switch_Write(LCD_D0_Pin|LCD_D1_Pin|LCD_D2_Pin|LCD_D3_Pin
            |LCD_D4_Pin|LCD_D5_Pin|LCD_D6_Pin|LCD_D7_Pin, GPIOB);

	RS_RESET;
	RD_SET;
	WR_RESET;
	DATAOUT(cmd);
	WR_SET;
	DATAOUT(0x00);


}

uint8_t LCD_READ_RET(){
	Switch_Read(LCD_D0_Pin|LCD_D1_Pin|LCD_D2_Pin|LCD_D3_Pin
            |LCD_D4_Pin|LCD_D5_Pin|LCD_D6_Pin|LCD_D7_Pin, GPIOB);

	RS_SET;
	WR_SET;
	RD_RESET;
	uint8_t parameter = DATAIN;
	RD_SET;

	return parameter;
}

void LCD_WRITE_PARAM(uint8_t param){

	RS_SET;
	RD_SET;
	DATAOUT(param);
	WR_RESET;
	WR_SET;
	DATAOUT(0x00);

}



void LCD_CMD_RAMRD(uint8_t* buff){


	LCD_SEND_CMD(0x2E);



	LCD_READ_RET(); //dummy
	buff[0] = LCD_READ_RET();
	buff[1] = LCD_READ_RET();
	buff[2] = LCD_READ_RET();
	buff[3] = LCD_READ_RET();
	buff[4] = LCD_READ_RET();
}

void LCD_CMD_RAMWR(uint8_t* buff, int length){


	LCD_SEND_CMD(0x2C);


	Switch_Write(LCD_D0_Pin|LCD_D1_Pin|LCD_D2_Pin|LCD_D3_Pin
            |LCD_D4_Pin|LCD_D5_Pin|LCD_D6_Pin|LCD_D7_Pin, GPIOB);

	for (int i = 0; i < length; i++){
		LCD_WRITE_PARAM(buff[i]);
	}

}

void LCD_FILL(uint16_t color){

	LCD_SEND_CMD(0x2C);

	Switch_Write(LCD_D0_Pin|LCD_D1_Pin|LCD_D2_Pin|LCD_D3_Pin
            |LCD_D4_Pin|LCD_D5_Pin|LCD_D6_Pin|LCD_D7_Pin, GPIOB);

	for (int i = 0; i < 76800; i++){
		LCD_WRITE_PARAM((uint8_t)color);
		LCD_WRITE_PARAM((uint8_t)color>>8);
	}
}

void LCD_FILL_AREA(uint16_t color, uint16_t width, uint16_t height, uint16_t origin_x, uint16_t origin_y){
	width--;
	int xend = width + origin_x;
	height--;
	int yend = height + origin_y;

	LCD_SEND_CMD(0x2A);
	LCD_WRITE_PARAM((uint8_t)(origin_x>>8));
	LCD_WRITE_PARAM((uint8_t)origin_x);
	LCD_WRITE_PARAM((uint8_t)(xend>>8));
	LCD_WRITE_PARAM((uint8_t)xend);

	LCD_SEND_CMD(0x2B);
	LCD_WRITE_PARAM((uint8_t)(origin_y>>8));
	LCD_WRITE_PARAM((uint8_t)origin_y);
	LCD_WRITE_PARAM((uint8_t)(yend>>8));
	LCD_WRITE_PARAM((uint8_t)yend);

	LCD_SEND_CMD(0x2C);

	for (int i = 0; i< height*width; i++){
		LCD_WRITE_PARAM((uint8_t)color);
		LCD_WRITE_PARAM((uint8_t)color>>8);
	}

}

void LCD_FILL_BUFFER_AREA(uint8_t* buffer, uint16_t width, uint16_t height, uint16_t origin_x, uint16_t origin_y){
	width--;
	uint16_t xend = width + origin_x;
	height--;
	uint16_t yend = height + origin_y;

	LCD_SEND_CMD(0x2A);
	LCD_WRITE_PARAM((uint8_t)(origin_x>>8));
	LCD_WRITE_PARAM((uint8_t)origin_x);
	LCD_WRITE_PARAM((uint8_t)(xend>>8));
	LCD_WRITE_PARAM((uint8_t)xend);

	LCD_SEND_CMD(0x2B);
	LCD_WRITE_PARAM((uint8_t)(origin_y>>8));
	LCD_WRITE_PARAM((uint8_t)origin_y);
	LCD_WRITE_PARAM((uint8_t)(yend>>8));
	LCD_WRITE_PARAM((uint8_t)yend);


	LCD_SEND_CMD(0x2C);

	for (int i = 0; i< height*width*2; i++){
		LCD_WRITE_PARAM(buffer[i]);

	}

}

void LCD_FILL_BUFFER_PART_START_AREA(uint8_t* buffer, uint16_t width, uint16_t height, uint16_t part, uint16_t origin_x, uint16_t origin_y){
	width--;
	uint16_t xend = width + origin_x;
	height--;
	uint16_t yend = height + origin_y;

	LCD_SEND_CMD(0x2A);
	LCD_WRITE_PARAM((uint8_t)(origin_x>>8));
	LCD_WRITE_PARAM((uint8_t)origin_x);
	LCD_WRITE_PARAM((uint8_t)(xend>>8));
	LCD_WRITE_PARAM((uint8_t)xend);

	LCD_SEND_CMD(0x2B);
	LCD_WRITE_PARAM((uint8_t)(origin_y>>8));
	LCD_WRITE_PARAM((uint8_t)origin_y);
	LCD_WRITE_PARAM((uint8_t)(yend>>8));
	LCD_WRITE_PARAM((uint8_t)yend);


	LCD_SEND_CMD(0x2C);

	//for (int i = 0; i< part; i++){
	//	LCD_WRITE_PARAM(buffer[i]);

	//}

}
void LCD_FILL_BUFFER_PART_CONTI_AREA(uint8_t* buffer, uint16_t part){

	//LCD_SEND_CMD(0x2C);

	for (int i = 0; i< part; i++){
		LCD_WRITE_PARAM(buffer[i]);

	}

}



void LCD_INIT(){
	Config_Control_Pins();
	CS_RESET;

	LCD_RESET();

	LCD_SEND_CMD(0xCF);
	LCD_WRITE_PARAM(0x00);
	LCD_WRITE_PARAM(0xC9); //C1
	LCD_WRITE_PARAM(0X30);
	LCD_SEND_CMD(0xED);
	LCD_WRITE_PARAM(0x64);
	LCD_WRITE_PARAM(0x03);
	LCD_WRITE_PARAM(0X12);
	LCD_WRITE_PARAM(0X81);
	LCD_SEND_CMD(0xE8);
	LCD_WRITE_PARAM(0x85);
	LCD_WRITE_PARAM(0x10);
	LCD_WRITE_PARAM(0x7A);
	LCD_SEND_CMD(0xCB);
	LCD_WRITE_PARAM(0x39);
	LCD_WRITE_PARAM(0x2C);
	LCD_WRITE_PARAM(0x00);
	LCD_WRITE_PARAM(0x34);
	LCD_WRITE_PARAM(0x02);
	LCD_SEND_CMD(0xF7);
	LCD_WRITE_PARAM(0x20);
	LCD_SEND_CMD(0xEA);
	LCD_WRITE_PARAM(0x00);
	LCD_WRITE_PARAM(0x00);
	LCD_SEND_CMD(0xC0);    //Power control
	LCD_WRITE_PARAM(0x1B);   //VRH[5:0]
	LCD_SEND_CMD(0xC1);    //Power control
	LCD_WRITE_PARAM(0x00);   //SAP[2:0];BT[3:0] 01
	LCD_SEND_CMD(0xC5);    //VCM control
	LCD_WRITE_PARAM(0x30); 	 //3F
	LCD_WRITE_PARAM(0x30); 	 //3C
	LCD_SEND_CMD(0xC7);    //VCM control2
	LCD_WRITE_PARAM(0XB7);
	LCD_SEND_CMD(0x36);    // Memory Access Control
	LCD_WRITE_PARAM(0x08);
	LCD_SEND_CMD(0x3A);    //Select 16 bit pixel mode
	LCD_WRITE_PARAM(0x55); //DPI / DBI = 101
	LCD_SEND_CMD(0xB1);
	LCD_WRITE_PARAM(0x00);
	LCD_WRITE_PARAM(0x1A);
	LCD_SEND_CMD(0xB6);    // Display Function Control
	LCD_WRITE_PARAM(0x0A);
	LCD_WRITE_PARAM(0xA2);
	LCD_SEND_CMD(0xF2);    // 3Gamma Function Disable
	LCD_WRITE_PARAM(0x00);
	LCD_SEND_CMD(0x26);    //Gamma curve selected
	LCD_WRITE_PARAM(0x01);
	LCD_SEND_CMD(0xE0);    //Set Gamma
	LCD_WRITE_PARAM(0x0F);
	LCD_WRITE_PARAM(0x2A);
	LCD_WRITE_PARAM(0x28);
	LCD_WRITE_PARAM(0x08);
	LCD_WRITE_PARAM(0x0E);
	LCD_WRITE_PARAM(0x08);
	LCD_WRITE_PARAM(0x54);
	LCD_WRITE_PARAM(0XA9);
	LCD_WRITE_PARAM(0x43);
	LCD_WRITE_PARAM(0x0A);
	LCD_WRITE_PARAM(0x0F);
	LCD_WRITE_PARAM(0x00);
	LCD_WRITE_PARAM(0x00);
	LCD_WRITE_PARAM(0x00);
	LCD_WRITE_PARAM(0x00);
	LCD_SEND_CMD(0XE1);    //Set Gamma
	LCD_WRITE_PARAM(0x00);
	LCD_WRITE_PARAM(0x15);
	LCD_WRITE_PARAM(0x17);
	LCD_WRITE_PARAM(0x07);
	LCD_WRITE_PARAM(0x11);
	LCD_WRITE_PARAM(0x06);
	LCD_WRITE_PARAM(0x2B);
	LCD_WRITE_PARAM(0x56);
	LCD_WRITE_PARAM(0x3C);
	LCD_WRITE_PARAM(0x05);
	LCD_WRITE_PARAM(0x10);
	LCD_WRITE_PARAM(0x0F);
	LCD_WRITE_PARAM(0x3F);
	LCD_WRITE_PARAM(0x3F);
	LCD_WRITE_PARAM(0x0F);
	LCD_SEND_CMD(0x2B);
	LCD_WRITE_PARAM(0x00);
	LCD_WRITE_PARAM(0x00);
	LCD_WRITE_PARAM(0x01);
	LCD_WRITE_PARAM(0x3f);
	LCD_SEND_CMD(0x2A);
	LCD_WRITE_PARAM(0x00);
	LCD_WRITE_PARAM(0x00);
	LCD_WRITE_PARAM(0x00);
	LCD_WRITE_PARAM(0xef);

	LCD_SEND_CMD(0x11); //Exit Sleep
	HAL_Delay(120);
	LCD_SEND_CMD(0x29); //display on

}

