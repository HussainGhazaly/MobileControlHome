/*
 * TIMER.h
 *
 *  Created on: Jan 31, 2020
 *      Author: Hussain
 */

#ifndef MCAL_TIMER_TIMER_H_
#define MCAL_TIMER_TIMER_H_

#include "std_types.h"

typedef enum {
	pre_stop = 0, pre_No_scaling, pre_8, pre_64, pre_256, pre_1024,
} Timer_PreScaler_t;

typedef enum {
	NORMAL = 0, CTC,
} Timer_Mode_t;

typedef enum {
	OC0_DIS = 0, OC0_TOG,
} Timer_OC0_t;

typedef enum {
	INT_DISABLE = 0, INT_EN,
} Timer_Interrupt_t;

typedef struct {
	Timer_PreScaler_t prescale;
	Timer_Mode_t mode;
	Timer_OC0_t OC0;
	Timer_Interrupt_t Is_interrupt;
	u8 timer_init_value;
} TIMER0_Config_t;

void Timer0_Start(TIMER0_Config_t configt);
void Timer0_Set_OCR(u8 valueC);
void Timer0_Stop(void);

#endif /* MCAL_TIMER_TIMER_H_ */
