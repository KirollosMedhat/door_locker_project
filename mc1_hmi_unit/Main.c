/*
 * Main.c
 *
 *  Created on: Jul 23, 2021
 *      Author: Kirollos
 */

#include "keypad.h"
#include "lcd.h"
#include "uart.h"
#include "timers.h"


#define F_CPU 8000000UL
#define M2_READY 0x10
#define PASSWORD_LENGTH 7
#define GET_PASSWORD 0x11
#define ALARM 0x12
#define GET_PASSWORD_FIRST_TIME 0x13
#define CORRECT_PASSWORD 0x14
#define WRONG_PASSWORD 0x15
#define DISPLAY_MENU 0x16
#define LOCK_THE_DOOR 0x17
#define RESET_PASSWORD 0x18


uint8 InputPassword[PASSWORD_LENGTH];

uint8 showMenu(){
	uint8 OptionNum;
	LCD_clearScreen();
	LCD_displayString("1)LOCK THE DOOR");
	LCD_goToRowColumn(1,0);
	LCD_displayString("2)RESET PASSWORD");
	OptionNum=Keypad_getPressedKey();
	if(OptionNum==1){
		return LOCK_THE_DOOR;
	}else if(OptionNum==2){
		return RESET_PASSWORD;
	}
}

void getPasswordFromKeypad(){
	uint8 i=0;
	LCD_clearScreen();
	LCD_displayString("Enter a password");
	_delay_ms(500);
	LCD_clearScreen();
	for(i=0; i<5; i++){
	InputPassword[i]=Keypad_getPressedKey();
	LCD_displayCharacter('*');
	}
	InputPassword[5]='#';
	InputPassword[6]='\0';
	LCD_clearScreen();
}

int main(void){
	uint8 UARTCommand=0;
	UARTconfig.BaudRate=9600;
	UARTconfig.DataBitsLength=8;
	UARTconfig.NumOfStopBits=1;
	UARTconfig.ParityType=2;
	UART_init(&UARTconfig);
	LCD_init();
    while(1){


//    	/***************************DEBUGGING SECTION****************************/
//
//    	LCD_clearScreen();
//    	LCD_displayString("Stuck here #4");
////    	_delay_ms(2000);
//
//    	/*=====================================================================*/



    	UARTCommand=UART_recieveByte();
    	if(UARTCommand==GET_PASSWORD_FIRST_TIME){
    		LCD_displayString("CreateNewPassword");
    		_delay_ms(1000);
//    		getPasswordFromKeypad();
//    		/***************************DEBUGGING SECTION****************************/
//
//    		LCD_clearScreen();
//    		LCD_displayString("Stuck here #1");
////    		_delay_ms(2000);
//
//    		/*=====================================================================*/

//    		UART_sendString(InputPassword);

//    		/***************************DEBUGGING SECTION****************************/
//
//    		LCD_clearScreen();
//    		LCD_displayString("Stuck here #2");
////	    		_delay_ms(2000);
//
//    		/*=====================================================================*/
    		UARTCommand=0;
    	}else if(UARTCommand==ALARM){
    		LCD_displayString("ALERT!!");
    		/*Stopping the MC from making any stop forward for 1min*/
    		_delay_ms(6000);
    		_delay_ms(6000);
    		_delay_ms(6000);
    		_delay_ms(6000);
    		_delay_ms(6000);
    		_delay_ms(6000);
    		_delay_ms(6000);
    		_delay_ms(6000);
    		_delay_ms(6000);
    		_delay_ms(6000);
    		UARTCommand=0;
    		//continue;
    	}else if(UARTCommand==GET_PASSWORD){
    		getPasswordFromKeypad();
    		UART_sendString(InputPassword);
    		UARTCommand=0;
    		//continue;
    	}else if(UARTCommand==CORRECT_PASSWORD){
    		LCD_clearScreen();
    		LCD_displayString("CORRECT PASSWORD");
    		_delay_ms(1000);
    		UARTCommand=0;
    	}else if(UARTCommand==WRONG_PASSWORD){
    		LCD_clearScreen();
    		LCD_displayString("WRONG PASSWORD");
    		_delay_ms(1000);
    		UARTCommand=0;
    		//continue;
    	}else if(UARTCommand==DISPLAY_MENU){
    		UART_sendByte(showMenu());
    	}
    }
}

