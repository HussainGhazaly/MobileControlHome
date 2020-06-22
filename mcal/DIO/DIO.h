/*
 * DIO.h
 *
 *  Created on: Dec 27, 2019
 *      Author: Ibrahim
 */

#ifndef MCAL_DIO_DIO_H_
#define MCAL_DIO_DIO_H_
#include "std_types.h"

typedef enum{
	GROUPA =0,
	GROUPB ,
	GROUPC ,
	GROUPD ,
}Group_t;

typedef enum{
	INPUT =0,
	OUTPUT,
}PIN_MODE_t;

typedef enum{
	LOW =0,
	HIGH,
}PIN_OUTPUT_t;

typedef enum{
	PIN_0 = 0,
	PIN_1,
	PIN_2,
	PIN_3,
	PIN_4,
	PIN_5,
	PIN_6,
	PIN_7,
}PIN_Num_t;

typedef enum{
	BIT_VALUE_0 = 0,
	BIT_VALUE_1 = 1
}BIT_VALUE_t ;

void DIO_SET_PIN_DIR(Group_t GROUPID ,PIN_Num_t PIN_NUM ,PIN_MODE_t PINMODE);
void DIO_SET_PIN_VALUE(Group_t GROUPID ,PIN_Num_t PIN_NUM ,PIN_OUTPUT_t PINLEVEL);
BIT_VALUE_t DIO_GET_PIN_VALUE(Group_t GROUPID ,PIN_Num_t PIN_NUM);

void DIO_SET_GROUP_DIR(Group_t GROUPID ,u8 dir);
void DIO_SET_GROUP_VALUE(Group_t GROUPID ,u8 val);
u8 DIO_GET_GROUP_VALUE(Group_t GROUPID);


u8 DIO_return_Group_value(Group_t GROUPID);






#endif /* MCAL_DIO_DIO_H_ */
