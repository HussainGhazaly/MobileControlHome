/*
 * PWM.h
 *
 *  Created on: Feb 1, 2020
 *      Author: hussain
 */

#ifndef MCAL_PWM_PWM_H_
#define MCAL_PWM_PWM_H_

#include "std_types.h"

void PWM_init(u16 top);
void PWM_set_Duty(u16 value);

#endif /* MCAL_PWM_PWM_H_ */
