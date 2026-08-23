/*
 * uart.c
 *
 *  Created on: Jul 20, 2021
 *      Author: Kirollos
 */
#include "uart.h"



void UART_init(struct UARTConfiguration *ptr){
	//Asynchronous Mode
	/*Number of stop bits*/
	if(ptr->NumOfStopBits==2){         	/*for two stop bits*/
		SET_BIT(UCSRC,USBS);			/*1 stop bit is the default*/
	}
	/*Character Size*/
	if(ptr->DataBitsLength==5){
		/*5 bit by default UCSZ0=0, UCSZ1=0, UCSZ2=0 */
	}else if(ptr->DataBitsLength==6){
		SET_BIT(UCSRC,UCSZ0);
	}else if(ptr->DataBitsLength==7){
		SET_BIT(UCSRC,UCSZ1);
	}else if(ptr->DataBitsLength==8){
		SET_BIT(UCSRC,UCSZ0);
		SET_BIT(UCSRC,UCSZ1);
	}
	/*Parity type*/

	if(ptr->ParityType==0){					/*Even Parity*/
		SET_BIT(UCSRC,UPM1);
	}else if(ptr->ParityType==1){			/*Odd Parity*/
		SET_BIT(UCSRC,UPM1);
		SET_BIT(UCSRC,UPM0);
	}else if(ptr->ParityType==2){
		/*Parity disabled by default*/
	}
	UCSRA|=(1<<U2X);
	UCSRC|=(1<<URSEL) | (1<<UCSZ1) | (1<<UCSZ0);
	UCSRB|=(1<<TXEN) | (1<<RXEN);
	UBRRL=BAUD_PRESCALE_DOUBLE_SPEED;
	UBRRH=BAUD_PRESCALE_DOUBLE_SPEED>>8;
}

void UART_sendByte(const uint8 data){
	while(BIT_IS_CLEAR(UCSRA,UDRE)){
	}
	UDR=data;
}

uint8 UART_recieveByte(){

	while(BIT_IS_CLEAR(UCSRA,RXC)){
	}

	return UDR;
}

void UART_sendString(const uint8 *str){
	uint8 i=0;
	for(i=0; str[i]!='\0'; i++){
//		/***************************DEBUGGING SECTION****************************/
//
//		LCD_clearScreen();
//		LCD_displayString("Stuck here #3");
////		_delay_ms(2000);
//
//		/*=====================================================================*/
		UART_sendByte(str[i]);
	}
}

void UART_recieveString(uint8 *str){
	uint8 i=0;
	str[i]=UART_recieveByte();
	while(str[i]!='#'){
		i++;
		str[i]=UART_recieveByte();
	}
	str[i]='\0';
}
