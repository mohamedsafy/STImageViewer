/*
 * TS_ILI9341.c
 *
 *  Created on: Apr 16, 2024
 *      Author: mohamed
 */


#include "ILI9341.h"
#include "TS_ILI9341.h"
#include "adc.h"
#include "lcd_pins.h"

#include <stdio.h>
#include <stdlib.h>


uint32_t xmax=0;
uint32_t ymax=0;


int comp (const void * elem1, const void * elem2)
{
    int f = *((int*)elem1);
    int s = *((int*)elem2);
    if (f > s) return  1;
    if (f < s) return -1;
    return 0;
}


volatile uint32_t TS_READ_X(){
	Switch_Write(XP, XP_PORT); //LCD_D0
	Switch_Write(XM, XM_PORT); //LCD_RS
	HAL_GPIO_WritePin(XP_PORT, XP, SET);
	HAL_GPIO_WritePin(XM_PORT, XM, RESET);

	Switch_Read(YM, YM_PORT); //LCD_D1
	Switch_Analog(YP, YP_PORT); //LCD_CS

	uint32_t samples[7];
	uint32_t sum = 0;
	for (int i = 0; i <7; i++){
		HAL_ADC_Start(&hadc_lcd);
		HAL_ADC_PollForConversion(&hadc_lcd, HAL_MAX_DELAY);
		samples[i] = HAL_ADC_GetValue(&hadc_lcd);
		sum+=samples[i];
	}

	qsort(samples, 7, sizeof(uint32_t), comp);
	return samples[3];
}

uint32_t TS_READ_Y(){
	Switch_Write(YP, YP_PORT); //LCD_CS
	Switch_Write(YM, YM_PORT); //LCD_D1
	HAL_GPIO_WritePin(YP_PORT, YP, SET);
	HAL_GPIO_WritePin(YM_PORT, YM, RESET);

	Switch_Read(XP, XP_PORT); //LCD_D0
	Switch_Analog(XM, XM_PORT); //LCD_RS

	uint32_t samples[7];
	uint32_t sum = 0;
	for (int i = 0; i <7; i++){
		HAL_ADC_Start(&hadc_lcd);
		HAL_ADC_PollForConversion(&hadc_lcd, HAL_MAX_DELAY);
		samples[i] = HAL_ADC_GetValue(&hadc_lcd);
		sum+=samples[i];
	}

	qsort(samples, 7, sizeof(uint32_t), comp);
	return samples[3];
}

int32_t TS_READ_Z(){
	Switch_Write(XP, XP_PORT); //LCD_D0
	Switch_Write(YM, YM_PORT); //LCD_D1
	HAL_GPIO_WritePin(XP_PORT, XP, RESET);
	HAL_GPIO_WritePin(YM_PORT, YM, SET);

	//Switch_Read(YP, YP_PORT);
	Switch_Analog(XM, XM_PORT); //LCD_RS

	uint32_t sample1;

	HAL_ADC_Start(&hadc_lcd);
	HAL_ADC_PollForConversion(&hadc_lcd, HAL_MAX_DELAY);
	sample1 = HAL_ADC_GetValue(&hadc_lcd);

	//Switch_Read(XM, XM_PORT);
	Switch_Analog(YP, YP_PORT); //LCD_CS

	uint32_t sample2;

	HAL_ADC_Start(&hadc_lcd);
	HAL_ADC_PollForConversion(&hadc_lcd, HAL_MAX_DELAY);
	sample2 = HAL_ADC_GetValue(&hadc_lcd);


	return 3900-sample2+sample1;
}


//Not Thread Safe
void TS_CALIBRATE(volatile uint32_t* xmaxl, volatile uint32_t* ymaxl, volatile uint32_t* pressure){

	if (TS_READ_Z() < 100){
		*pressure = 0;
		*xmaxl = 0;
		*ymaxl = 0;
		return;
	}
	uint32_t temp1= TS_READ_X();
	uint32_t temp2= TS_READ_Y();

	if(temp1 > xmax)
		xmax=temp1;
	if(temp2 > ymax)
		ymax=temp2;

	*xmaxl = xmax;
	*ymaxl = ymax;
	*pressure=1;

}

void TS_READ_XY(volatile uint32_t* x, volatile uint32_t* y, volatile uint32_t* pressure){
	MX_ADC1_Init();

	if (TS_READ_Z() < 100){
		*pressure=0;
		*x = 0;
		*y = 0;
		HAL_ADC_DeInit(&hadc_lcd);

		Switch_Write(YM, YM_PORT);
		Switch_Write(YP, YP_PORT);
		Switch_Write(XM, XM_PORT);
		Switch_Write(XP, XP_PORT);

		CS_RESET;
		return;
	}
	uint32_t temp1= (((float)TS_READ_X()-695)/3400)*240;
	uint32_t temp2= ((((float)TS_READ_Y()-132)/3400)*320);
	*x = temp1;
	*y = temp2;
	*pressure=1;

	HAL_ADC_DeInit(&hadc_lcd);

	Switch_Write(YM, YM_PORT);
	Switch_Write(YP, YP_PORT);
	Switch_Write(XM, XM_PORT);
	Switch_Write(XP, XP_PORT);

	CS_RESET;

}
