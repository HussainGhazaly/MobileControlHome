/*
 * PWM.c
 *
 *  Created on: Feb 1, 2020
 *      Author: hussain
 */


#include "PWM.h"
#include "avr/io.h"
#include "math.h"
void PWM_init(u16 top)
{
	//set prescaler with 1024
	SET_BIT(TCCR1B,0);
	SET_BIT(TCCR1B,2);

	//set mode with fast PWM -- top ICR1
	CLEAR_BIT(TCCR1A,0);
	SET_BIT(TCCR1A,1);
	SET_BIT(TCCR1B,3);
	SET_BIT(TCCR1B,4);

	//clear FOC1A due to pwm mode
	CLEAR_BIT(TCCR1A,3);

	//set OC1A as non inverted
	CLEAR_BIT(TCCR1A,6);
	SET_BIT(TCCR1A,7);

	// set passed top to ICR1
	/*      /|	----	top --- ICR1
	 *    /  |
	 *  /    |
	  /      |
	  --------
	 */
	ICR1 = top;
	TCNT1 = 0x0000;

}
void PWM_set_Duty(u16 value)
{
OCR1A = value;
}


