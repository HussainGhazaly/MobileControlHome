/*
 * KEYPAD.c
 *
 *  Created on: Jan 10, 2020
 *      Author: hussa
 */

#include "KEYPAD.h"
#include "util/delay.h"
#define ROW_MAX 4
#define COL_MAX 4
u8 KeyPad_Arr[ROW_MAX][COL_MAX] =
{
		{1 , 2 , 3 , 'A'},
		{4 , 5 , 6 , 'B'},
		{7 , 8 , 9 , 'C'},
		{'#' , 0 , '*' , 'D'}
};

void KeyPad_init(KeyPad_CFG_t KeyPad_CFG)
{

		DIO_SET_GROUP_DIR(KeyPad_CFG.GroupID,0x0F);

}

/*
 * this function return the number which pressed.
 *  input : struct of CFG keypad.
 *  output : u8.
 * connection of pins
 * R1 --> pin0
 * R2 --> pin1
 * R3 --> pin2
 * R4 --> pin3
 * C1 --> pin4
 * C2 --> pin5
 * C3 --> pin6
 * C4 --> pin7
 */
u8 KeyPad_get_KeyPressed(KeyPad_CFG_t KeyPad_CFG)
{
	u8 row=0;
	u8 col = 0;
	u8 keyNum = 255;
	for ( row = 0 ; row <KeyPad_CFG.Row_num ;row++)
	{
		DIO_SET_GROUP_VALUE(KeyPad_CFG.GroupID , (~(0b00000001 << row)));
		_delay_ms(10);
		for(col = 0 ; col < KeyPad_CFG.Col_num ; col++)
		{
			if(!(DIO_GET_GROUP_VALUE(KeyPad_CFG.GroupID) & (1<< (col+4))) )
			{
				keyNum =  KeyPad_Arr[row][col];
			}
		}
		_delay_ms(10);
	}
	return keyNum;
}
