/*
 * ADC.c
 *
 *  Created on: Jan 24, 2020
 *      Author: hussa
 */


/*
 * ADC.c
 *
 *  Created on: Jan 24, 2020
 *      Author: Ibrahim
 */

#include "ADC.h"
#include "math.h"
void ADC_init(void) {
	// ADC Enable
	SET_BIT(ADCSRA_Reg, 7);

	// Prescaler Configuration as 128
	SET_BIT(ADCSRA_Reg, 2);
	SET_BIT(ADCSRA_Reg, 1);
	SET_BIT(ADCSRA_Reg, 0);

	//AREF
	CLEAR_BIT(ADMUX_Reg, 7);
	CLEAR_BIT(ADMUX_Reg, 6);

	// ADC Data Rgith Adjustment
	CLEAR_BIT(ADMUX_Reg, 5);
}
u16 ADC_Read(u8 channel) {

	// ADC Channel Selection
	if (channel < 7) {
		// clear first fifth bits
		ADMUX_Reg &= 0xE0;
		ADMUX_Reg |= channel;

		// Start Single Convertion
		SET_BIT(ADCSRA_Reg, 6);

		//wait for the conversion
		/*
		 * 0001 0000 (1<<4)
		 * &
		 * 1110 0111 ADCSRA
		 * ----------
		 * 0000 0000 not false
		 * true
		 * -------------------
		 * 0001 0000 (1<<4)
		 * &
		 * 1111 0111 ADCSRA
		 * ----------
		 * 0001 0000 not true
		 * false
		 *
		 */


		while (!(ADCSRA_Reg & (1 << 4)));

		//ADC Flag Clear
		SET_BIT(ADCSRA_Reg, 4);
	}
	else
	{

	}
	return ADC_Reg;
}
