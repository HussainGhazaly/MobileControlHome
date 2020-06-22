/*
 * UART.c
 *
 *  Created on: 14 Feb 2020
 *      Author: 	Hussain
 */

#include "UART.h"
#include "math.h"
#include "avr/io.h"


void UART_init(u16 baudrate) {
u16 baud= (F_CPU/(8.0*baudrate)) - 1;

UBRRL = (u8) baud;
UBRRH = (baud>>8);

// double speed enable
SET_BIT(UCSRA,1);

// to ensure that register is zero
UCSRB = 0x00;
// enable TX in uart
SET_BIT(UCSRB,3);

// enable RX in uart
SET_BIT(UCSRB,4);

UCSRC = 0x00;
//enable to wirte in UCSRC
SET_BIT(UCSRC,7);

//select 8-bit mode
SET_BIT(UCSRC,2);
SET_BIT(UCSRC,1);


}
void UART_write(u8 data) {

	while(GET_BIT_VALUE(UCSRA,5) == 0);
	UDR = data;
}

u8 UART_read(void) {
	while (GET_BIT_VALUE(UCSRA,7) == 0);
	return UDR;
}

void UART_Print(char* Str)
{
	while(*Str)
	{
		UART_write(*Str);
		Str++;
	}
}
