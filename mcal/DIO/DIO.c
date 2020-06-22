/*
 * DIO.c
 *
 *  Created on: Dec 27, 2019
 *      Author: Ibrahim
 */

#include "std_types.h"
#include "DIO.h"
#include "math.h"
/* Group A Registers */
#define PORTA_Register  *((volatile u8*)0x3B)
#define DDRA_Register   *((volatile u8*)0x3A)
#define PINA_Register   *((volatile u8*)0x39)

/* Group B Registers */
#define PORTB_Register  *((volatile u8*)0x38)
#define DDRB_Register   *((volatile u8*)0x37)
#define PINB_Register   *((volatile u8*)0x36)

/* Group C Registers */
#define PORTC_Register  *((volatile u8*)0x35)
#define DDRC_Register   *((volatile u8*)0x34)
#define PINC_Register   *((volatile u8*)0x33)

/* Group D Registers */
#define PORTD_Register  *((volatile u8*)0x32)
#define DDRD_Register   *((volatile u8*)0x31)
#define PIND_Register   *((volatile u8*)0x30)

void DIO_SET_PIN_DIR(Group_t GROUPID, PIN_Num_t PIN_NUM, PIN_MODE_t PINMODE) {
	if (PINMODE == OUTPUT) {
		switch (GROUPID) {
		case GROUPA:
			SET_BIT(DDRA_Register, PIN_NUM);
			break;
		case GROUPB:
			SET_BIT(DDRB_Register, PIN_NUM);
			break;
		case GROUPC:
			SET_BIT(DDRC_Register, PIN_NUM);
			break;
		case GROUPD:
			SET_BIT(DDRD_Register, PIN_NUM);
			break;
		}
	} else if (PINMODE == INPUT) {
		switch (GROUPID) {
		case GROUPA:
			CLEAR_BIT(DDRA_Register, PIN_NUM);
			break;
		case GROUPB:
			CLEAR_BIT(DDRB_Register, PIN_NUM);
			break;
		case GROUPC:
			CLEAR_BIT(DDRC_Register, PIN_NUM);
			break;
		case GROUPD:
			CLEAR_BIT(DDRD_Register, PIN_NUM);
			break;
		}
	} else {
		//		#warning ("the input is not acceptable")
	}
}
void DIO_SET_PIN_VALUE(Group_t GROUPID, PIN_Num_t PIN_NUM, PIN_OUTPUT_t PINLEVEL) {
	if (PINLEVEL == HIGH) {
		switch (GROUPID) {
		case GROUPA:
			SET_BIT(PORTA_Register, PIN_NUM);
			break;
		case GROUPB:
			SET_BIT(PORTB_Register, PIN_NUM);
			break;
		case GROUPC:
			SET_BIT(PORTC_Register, PIN_NUM);
			break;
		case GROUPD:
			SET_BIT(PORTD_Register, PIN_NUM);
			break;
		}
	} else if (PINLEVEL == LOW) {
		switch (GROUPID) {
		case GROUPA:
			CLEAR_BIT(PORTA_Register, PIN_NUM);
			break;
		case GROUPB:
			CLEAR_BIT(PORTB_Register, PIN_NUM);
			break;
		case GROUPC:
			CLEAR_BIT(PORTC_Register, PIN_NUM);
			break;
		case GROUPD:
			CLEAR_BIT(PORTD_Register, PIN_NUM);
			break;
		}
	} else {
		//			#warning ("the input is not accaptable")
	}
}

BIT_VALUE_t DIO_GET_PIN_VALUE(Group_t GROUPID, PIN_Num_t PIN_NUM) {
	BIT_VALUE_t BIT_VAL = BIT_VALUE_0;
	switch (GROUPID) {
	case GROUPA:
		BIT_VAL = GET_BIT_VALUE(PINA_Register, PIN_NUM);
		break;
	case GROUPB:
		BIT_VAL = GET_BIT_VALUE(PINB_Register, PIN_NUM);
		break;
	case GROUPC:
		BIT_VAL = GET_BIT_VALUE(PINC_Register, PIN_NUM);
		break;
	case GROUPD:
		BIT_VAL = GET_BIT_VALUE(PIND_Register, PIN_NUM);
		break;
	}
	return BIT_VAL;
}
void DIO_SET_GROUP_DIR(Group_t GROUPID, u8 dir) {
	switch (GROUPID) {
	case GROUPA:
		DDRA_Register = dir;
		break;
	case GROUPB:
		DDRB_Register = dir;
		break;
	case GROUPC:
		DDRC_Register = dir;
		break;
	case GROUPD:
		DDRD_Register = dir;
		break;
	}
}
u8 DIO_return_Group_value(Group_t GROUPID) {
	switch (GROUPID) {
	case GROUPA:
		return PORTA_Register ;
		break;
	case GROUPB:
		return PORTB_Register;
		break;
	case GROUPC:
		return PORTC_Register;
		break;
	case GROUPD:
		return PORTD_Register;
		break;
	}
	return 0;
}

void DIO_SET_GROUP_VALUE(Group_t GROUPID, u8 val) {
	switch (GROUPID) {
	case GROUPA:
		PORTA_Register = val;
		break;
	case GROUPB:
		PORTB_Register = val;
		break;
	case GROUPC:
		PORTC_Register = val;
		break;
	case GROUPD:
		PORTD_Register = val;
		break;
	}
}
u8 DIO_GET_GROUP_VALUE(Group_t GROUPID) {
	u8 value;
	switch (GROUPID) {
	case GROUPA:
		value = PINA_Register;
		break;
	case GROUPB:
		value = PINB_Register;
		break;
	case GROUPC:
		value = PINC_Register;
		break;
	case GROUPD:
		value = PIND_Register;
		break;
	}
	return value;
}
