/*
 * MobileControlledHome.c
 */
#define F_CPU 8000000UL
#include <util/delay.h>
#include "DIO.h"
#include <avr/interrupt.h>
#include "LCD.h"
#include "math.h"
#include "TIMER.h"
#include "PWM.h"
#include <avr/io.h>
#include "stdlib.h"
#include <stdio.h>
#include <string.h>
#include "UART.h"

char UserNames[10][15] =
{
	"USER1",
	"USER2",
	"USER3",
	"USER4",
	"USER5",
	"USER6",
	"USER7",
	"USER8",
	"USER9",
	"USER10"
};

char Passwords[10][10] =
{
	"USER1",
	"USER2",
	"USER3",
	"USER4",
	"USER5",
	"USER6",
	"USER7",
	"USER8",
	"USER9",
	"USER10"
};

void OpenDoor()
{
	DIO_SET_PIN_VALUE(GROUPA,PIN_0,HIGH);//Solenoid ON
	_delay_ms(1000);
	DIO_SET_PIN_VALUE(GROUPA,PIN_0,LOW);//Solenoid OFF
	_delay_ms(1000);
}
void LIGHTON()
{
	DIO_SET_PIN_VALUE(GROUPA,PIN_1,HIGH);//LIGHT ON
	_delay_ms(1000);
}
void LIGHTOFF()
{
	DIO_SET_PIN_VALUE(GROUPA,PIN_1,LOW);//LIGHT OFF
	_delay_ms(1000);
}
void AlarmON()
{
	TIMER0_Config_t timer0;
	timer0.Is_interrupt = INT_DISABLE;
	timer0.mode = CTC;
	timer0.prescale= pre_1024;
	timer0.timer_init_value = 0;
	timer0.OC0 = OC0_TOG;
	Timer0_Set_OCR(255);
	Timer0_Start(timer0);
}
void AlarmOFF()
{
	Timer0_Stop();
	DIO_SET_PIN_VALUE(GROUPB,PIN_3,LOW);//BUZZER OFF
}
int main(void)
{
	u8 ReceivedChar = 0x00;
	char ReceiveBuffer[100];
	char UserName[15];
	char Validate = 0;
	char Password[10];
	char Operation[10];
	u8 ReceiveIndex = 0;
	u8 SliceIndex = 0;
	char* COMMAND;
	char Slice[100];
	char* pch;
	char ALarm = 0;
	char Try = 0;
	DIO_SET_PIN_DIR(GROUPA,PIN_0,OUTPUT);//DOOR Solenoid
	DIO_SET_PIN_DIR(GROUPA,PIN_1,OUTPUT);//Light Bulb
	DIO_SET_PIN_DIR(GROUPB,PIN_3,OUTPUT);//BUZZER law 3mal 3 mrat 8alat
	UART_init(9600);
	UART_Print("System Start....\r\n");
	while(1)
	{
		ReceivedChar = UART_read();
		ReceiveBuffer[ReceiveIndex++] = ReceivedChar;
		if(ReceivedChar == '\r')//New Command Received
		{
			/*COMMAND FORMAT
			 *LOG USERNAME PASSWORD OPEN
			 *LOG USERNAME PASSWORD ON
			 *LOG USERNAME PASSWORD OFF
			 *LOG USER1 USER2 OPEN
			 *LOG USER1 USER1 OPEN
			 */
			//1-Search For LOG
			COMMAND = strstr(ReceiveBuffer, "LOG");
			if(COMMAND != NULL)
			{
				memset(UserName,'\0',15);
				memset(Password,'\0',10);
				memset(Operation,'\0',10);
				//2-SPLIT COMMAND BY SPACE
				pch = strtok (ReceiveBuffer," ");
				SliceIndex = 0;
				while (pch != NULL)
				{
					switch(SliceIndex)
					{
					case 0:
						break;
					case 1:
						strcpy(UserName,pch);
						break;
					case 2:
						strcpy(Password,pch);
						break;
					case 3:
						strcpy(Operation,pch);
						break;
					default:
						break;
					}
					pch = strtok (NULL, " ");
					SliceIndex++;
				};

				if(SliceIndex != 4)
				{
					UART_Print("BAD COMMAND\r\n");
				}
				else
				{
					memset(Slice,100,'\0');
					//LOG USERNAME PASSWORD OPEN
					snprintf (Slice,100,"USER NAME : %s\r\nPassword  : %s\r\nOPERATION : %s\r\n",UserName,Password,Operation);
					UART_Print(Slice);
					//3-Validate Login
					Validate = 0;
					for(int i=0;i<10;i++)
					{
						if(strstr(UserName,UserNames[i]) != NULL)
						{
							if(strstr(Password,Passwords[i]) != NULL)
							{
								Validate = 1;
								ALarm = 0;
								Try = 0;
								AlarmOFF();
								//4-Execute Operation
								if(strstr(Operation,"OPEN") != NULL)
								{
									OpenDoor();
									UART_Print("OK\r\n");
								}
								else if(strstr(Operation,"ON") != NULL)
								{
									LIGHTON();
									UART_Print("OK\r\n");
								}
								else if(strstr(Operation,"OFF") != NULL)
								{
									LIGHTOFF();
									UART_Print("OK\r\n");
								}
								else
								{
									UART_Print("Operation Fail!!\r\n");
								}
							}
						}
					}
					if(Validate == 0)
					{
						UART_Print("Wrong User Name Or Password!!\r\n");
						Try++;
						if(Try >= 3)
						{
							ALarm = 1;
							AlarmON();
						}
					}
				}
			}
			else
			{
				UART_Print("BAD COMMAND\r\n");
			}
			//Clear Buffer
			memset(ReceiveBuffer,'\0',100);
			ReceiveIndex = 0;
		}
		else if(ReceiveIndex >= 100)//Reset Buffer
		{
			memset(ReceiveBuffer,'\0',100);
			ReceiveIndex = 0;
		}
		else//Continue Receiving....
		{

		}
	}
	return 0;
}
