/*
 * lcd_pins.c
 *
 *  Created on: Apr 16, 2024
 *      Author: mohamed
 */
#include "lcd_pins.h"
#include "adc.h"


void Config_Control_Pins(){
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	GPIO_InitStruct.Pin = LCD_RD_Pin|LCD_WR_Pin|LCD_RS_Pin|LCD_CS_Pin|LCD_RST_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void Switch_Read(uint16_t pins, GPIO_TypeDef* port){
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	  GPIO_InitStruct.Pin = pins;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(port, &GPIO_InitStruct);
}

void Switch_Write(uint16_t pins, GPIO_TypeDef* port){
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	  GPIO_InitStruct.Pin = pins;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(port, &GPIO_InitStruct);
}

void Switch_Analog(uint16_t pins, GPIO_TypeDef* port){

	ADC_ChannelConfTypeDef sConfig = {0};

	sConfig.Channel = 31 - __builtin_clz(pins);
	sConfig.Rank = ADC_REGULAR_RANK_1;
	sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
	if (HAL_ADC_ConfigChannel(&hadc_lcd, &sConfig) != HAL_OK)
	{
		Error_Handler();
	}
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	  GPIO_InitStruct.Pin = pins;
	  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	  HAL_GPIO_Init(port, &GPIO_InitStruct);

}
