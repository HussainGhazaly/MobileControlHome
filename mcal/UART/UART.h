/*
 * UART.h
 *
 *  Created on: 14 Feb 2020
 *      Author: Hussain
 */

#ifndef MCAL_UART_UART_H_
#define MCAL_UART_UART_H_
#include "std_types.h"

void UART_init(u16 baudrate);
void UART_write(u8 data);
u8 UART_read(void);
void UART_Print(char* Str);
#endif /* MCAL_UART_UART_H_ */
