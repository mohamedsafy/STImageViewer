/*
 * TS_ILI9341.h
 *
 *  Created on: Apr 16, 2024
 *      Author: mohamed
 */

#ifndef INC_TS_ILI9341_H_
#define INC_TS_ILI9341_H_

void TS_READ_XY(volatile uint32_t* x, volatile uint32_t* y, volatile uint32_t* z);
volatile uint32_t TS_READ_X();
volatile uint32_t TS_READ_Y();
volatile int32_t TS_READ_Z();
void TS_CALIBRATE(volatile uint32_t* xmaxl, volatile uint32_t* ymaxl, volatile uint32_t* pressure);

#endif /* INC_TS_ILI9341_H_ */
