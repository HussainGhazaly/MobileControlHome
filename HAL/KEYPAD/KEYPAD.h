/*
 * KEYPAD.h
 *
 *  Created on: Jan 10, 2020
 *      Author: hussa
 */

#ifndef HAL_KEYPAD_KEYPAD_H_
#define HAL_KEYPAD_KEYPAD_H_

#include "std_types.h"
#include "DIO.h"
typedef enum{
	ROW_1 = 0,
	ROW_2,
	ROW_3,
	ROW_4,
}Row_t;

typedef enum{
	COL_1 = 0,
	COL_2,
	COL_3,
	COL_4,
}Col_t;

typedef struct
{
Group_t GroupID;
Row_t Row_num;
Col_t Col_num;
//u8 *ptrToArray;
}KeyPad_CFG_t;

void KeyPad_init(KeyPad_CFG_t KeyPad_CFG);
u8 KeyPad_get_KeyPressed(KeyPad_CFG_t KeyPad_CFG);
#endif /* HAL_KEYPAD_KEYPAD_H_ */

