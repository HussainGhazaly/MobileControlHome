/*
 * LCD.c

 *
 *  Created on: Jan 3, 2020
 *      Author: Yehia
 */

#include "LCD.h"
#include "util/delay.h"
#define lcd_Clear           0x01          /* replace all characters with ASCII 'space'                       */
#define lcd_Home            0x02          /* return cursor to first position on first line                   */
#define lcd_EntryMode       0x06          // shift cursor from left to right on read/write
#define lcd_DisplayOff      0x08          // turn display off
#define lcd_DisplayOn       0x0C          // display on, cursor off, don't blink character
#define lcd_FunctionReset   0x30          // reset the LCD
#define lcd_FunctionSet8bit 0x38          // 8-bit data, 2-line display, 5 x 7 font
#define lcd_SetCursor       0x80          // set cursor position

void LCD_init(LCD_CFG_t LCD_CFG)
{
	DIO_SET_GROUP_DIR(LCD_CFG.GroupData,0xff);
	DIO_SET_PIN_DIR(LCD_CFG.LCD_CNT.GroupControl,LCD_CFG.LCD_CNT.RS_PIN
			,OUTPUT);
	DIO_SET_PIN_DIR(LCD_CFG.LCD_CNT.GroupControl,LCD_CFG.LCD_CNT.E_PIN
				,OUTPUT);
	/* Delay 30ms to ensure the initialization of the LCD driver */
	_delay_ms(30);

	/* Return Home  */
	LCD_write_command(LCD_CFG ,lcd_Home);
	_delay_ms(15);

	/* Function Set  */
	LCD_write_command(LCD_CFG ,lcd_FunctionSet8bit);
	_delay_ms(1);

	/* Display ON OFF Control */
	LCD_write_command(LCD_CFG ,lcd_DisplayOn);
	_delay_ms(1);

	/* Clear Display */
	LCD_write_command(LCD_CFG ,lcd_Clear);
	_delay_ms(15);

	/* Entry Mode Set  */
	LCD_write_command(LCD_CFG ,lcd_EntryMode);
	_delay_ms(2);
}
void LCD_write_data(LCD_CFG_t LCD_CFG , u8 data)
{
	/* Set RS to LOW */
	DIO_SET_PIN_VALUE(LCD_CFG.LCD_CNT.GroupControl,
			LCD_CFG.LCD_CNT.RS_PIN,HIGH);
	/* Set E to HIGH  */
	DIO_SET_PIN_VALUE(LCD_CFG.LCD_CNT.GroupControl,
			LCD_CFG.LCD_CNT.E_PIN,HIGH);
	/* Load Command on Data bus */
	DIO_SET_GROUP_VALUE(LCD_CFG.GroupData,data);
	/* Set E to LOW */
	DIO_SET_PIN_VALUE(LCD_CFG.LCD_CNT.GroupControl,
			LCD_CFG.LCD_CNT.E_PIN,LOW);
	/* Wait for E to settle */
	_delay_ms(5);
	/* Set E to HIGH */
	DIO_SET_PIN_VALUE(LCD_CFG.LCD_CNT.GroupControl,
			LCD_CFG.LCD_CNT.E_PIN,HIGH);
	/* Delay for 10ms to let the LCD execute command */
	_delay_ms(10);
}
void LCD_write_command(LCD_CFG_t LCD_CFG , u8 command)
{
	/* Set RS to LOW */
	DIO_SET_PIN_VALUE(LCD_CFG.LCD_CNT.GroupControl,
			LCD_CFG.LCD_CNT.RS_PIN,LOW);
	/* Set E to HIGH  */
	DIO_SET_PIN_VALUE(LCD_CFG.LCD_CNT.GroupControl,
			LCD_CFG.LCD_CNT.E_PIN,HIGH);
	/* Load Command on Data bus */
	DIO_SET_GROUP_VALUE(LCD_CFG.GroupData,command);
	/* Set E to LOW */
	DIO_SET_PIN_VALUE(LCD_CFG.LCD_CNT.GroupControl,
			LCD_CFG.LCD_CNT.E_PIN,LOW);
	/* Wait for E to settle */
	_delay_ms(5);
	/* Set E to HIGH */
	DIO_SET_PIN_VALUE(LCD_CFG.LCD_CNT.GroupControl,
			LCD_CFG.LCD_CNT.E_PIN,HIGH);
	/* Delay for 10ms to let the LCD execute command */
	_delay_ms(10);
}
void LCD_write_string(LCD_CFG_t LCD_CFG , u8* string)
{
	u8 u8Index = 0;
	/* loop until the null character*/
	while (string[u8Index] != '\0')
	{
		/* Write Character on LCD */
		LCD_write_data(LCD_CFG,string[u8Index]);
		/* Increment local loop index */
		u8Index++;
		/* Delay to let the LCD show the character */
		_delay_ms(2);
	}
}
void LCD_goto_xy(LCD_CFG_t LCD_CFG , COL_t col , ROW_t row)
{
	if (col >= col_0 && col <= col_15)
	{
		switch(row)
		{
		case row_0 : LCD_write_command(LCD_CFG ,(lcd_SetCursor | col));
			break;
		case row_1 : LCD_write_command(LCD_CFG ,(lcd_SetCursor | (0x40+col)));
			break;
		default:
			break;
		}
	}
}
