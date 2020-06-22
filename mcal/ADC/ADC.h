/*
 * ADC.h
 *
 *  Created on: Jan 24, 2020
 *      Author: Ibrahim
 */

#ifndef MCAL_ADC_ADC_H_
#define MCAL_ADC_ADC_H_
#include "std_types.h"
#define ADMUX_Reg 	*((volatile u8*)0x27) 	// ADC Multiplexer Register
#define ADCSRA_Reg 	*((volatile u8*)0x26) 	// ADC Control And Status Register
#define ADC_Reg 	*((volatile u16*)0x24) 		// ADC BASE address Register

void ADC_init(void);
u16 ADC_Read(u8 channel);

#endif /* MCAL_ADC_ADC_H_ */


