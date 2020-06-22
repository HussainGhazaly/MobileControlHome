 /*
 * TIMER..c
 *
 *  Created on: Jan 31, 2020
 *      Author: Ibrahim
 */

#include "TIMER.h"
#include "math.h"

#define TCCR0_Reg *((volatile u8*)0x53)
#define TCNT0_Reg *((volatile u8*)0x52)
#define OCR0_Reg *((volatile u8*)0x5C)
#define TIMSK_Reg *((volatile u8*)0x59)
#define TIFR_Reg *((volatile u8*)0x58)

void Timer0_Start(TIMER0_Config_t configt) {
	TCCR0_Reg = 0x00;
	TCCR0_Reg |= configt.prescale;
	// non_pwm mode
	SET_BIT(TCCR0_Reg, 7);
	if (configt.mode == NORMAL) {

		if (configt.Is_interrupt == INT_EN) {
			// enable overflow interrupt
			SET_BIT(TIMSK_Reg, 0);
		}

	} else if (configt.mode == CTC) {
		if (configt.Is_interrupt == INT_EN) {
			// enable CTC interrupt
			SET_BIT(TIMSK_Reg, 1);
		}
		// enable mode CTC
		SET_BIT(TCCR0_Reg, 3);
		// set oc0 mode
		TCCR0_Reg |= (configt.OC0 << 4);
	} else {

	}
	// set the inital value of tcnt0
	TCNT0_Reg = configt.timer_init_value;

}


void Timer0_Set_OCR(u8 valueC)
{
	OCR0_Reg = valueC;
}

void Timer0_Stop(void)
{
	TCCR0_Reg = 0x00;
}
