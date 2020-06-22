/*
 * LCD.h
 *
 *  Created on: Jan 3, 2020
 *      Author: Yehia
 */


#ifndef HAL_LCD_LCD_H_
#define HAL_LCD_LCD_H_

#include "std_types.h"
#include "DIO.h"
// struct for control the lcd

typedef struct{
	Group_t GroupControl;
	PIN_Num_t RS_PIN;
	PIN_Num_t E_PIN;
}LCD_CNT_t;

typedef struct{
	Group_t GroupData;
	LCD_CNT_t LCD_CNT;
}LCD_CFG_t;

typedef enum
{
	row_0 = 0,
	row_1,
}ROW_t;
typedef enum
{
	col_0 = 0,
	col_1,
	col_2,
	col_3,
	col_4,
	col_5,
	col_6,
	col_7,
	col_8,
	col_9,
	col_10,
	col_11,
	col_12,
	col_13,
	col_14,
	col_15,

}COL_t;
void LCD_init(LCD_CFG_t LCD_CFG);
void LCD_write_data(LCD_CFG_t LCD_CFG , u8 data);
void LCD_write_command(LCD_CFG_t LCD_CFG , u8 command);
void LCD_write_string(LCD_CFG_t LCD_CFG , u8* string);
void LCD_goto_xy(LCD_CFG_t LCD_CFG , u8 col , u8 row);

#endif /* HAL_LCD_LCD_H_ */
