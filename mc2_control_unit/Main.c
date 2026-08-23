/*
 * Main.c
 *
 *  Created on: Jul 23, 2021
 *      Author: Kirollos
 */

#include "EEPROM.h"
#include "timers.h"
#include "uart.h"


#define F_CPU 8000000UL
#define PASSWORD_FIRST_ADDRESS 0x0001
#define M2_READY 0x10
#define PASSWORD_LENGTH 6
#define GET_PASSWORD 0x11
#define IS_IT_FIRST_TIME_ADDRESS 0x0000
#define ALARM 0x12
#define GET_PASSWORD_FIRST_TIME 0x13
#define CORRECT_PASSWORD 0x14
#define WRONG_PASSWORD 0x15
#define DISPLAY_MENU 0x16
#define LOCK_THE_DOOR 0x17
#define RESET_PASSWORD 0x18


uint8 IsItFirstTime;
static uint8 NumberOfFalseTrials=0;
uint8 SavedPasswordEEPROM[PASSWORD_LENGTH];
uint8 InputPassword[PASSWORD_LENGTH];

void stopMotor();
uint8 passwordChecker();
void motorAntiClockWise();
void motorClockWise();

void timerRoutine(){
	static uint16 tick=0;
	tick++;
	if(tick==458){
		stopMotor();
		motorAntiClockWise();
	}else if(tick==2*485){
		tick=0;
		stopMotor();
		TIMER_stop();
	}
}

void stopMotor(){
	CLEAR_BIT(PORTD,PD5);
	CLEAR_BIT(PORTD,PD6);
	CLEAR_BIT(PORTD,PD7);
}

void motorClockWise(){
	DDRD |= 0xE0;
	SET_BIT(PORTD,PD6);
	SET_BIT(PORTD,PD7);
}

void motorAntiClockWise(){
	DDRD |= 0xE0;
	SET_BIT(PORTD,PD5);
	SET_BIT(PORTD,PD7);
}

void createNewPassword(){
	uint8 i=0;

//	/***************************DEBUGGING SECTION****************************/
//
//	LCD_clearScreen();
//	LCD_displayString("Stuck here #8");
////	_delay_ms(2000);
//
//	/*=====================================================================*/


	UART_sendByte(GET_PASSWORD);
	UART_recieveString(InputPassword);




//	/***************************DEBUGGING SECTION****************************/
//
//	LCD_clearScreen();
//	LCD_displayString("Stuck here #9");
////	_delay_ms(2000);
//
//	/*=====================================================================*/

	for(i=0; i<5; i++){
		EEPROM_writeByte((i+PASSWORD_FIRST_ADDRESS),InputPassword[i]);
		SavedPasswordEEPROM[i]=InputPassword[i];
		_delay_ms(10);
	}
	EEPROM_writeByte((5+PASSWORD_FIRST_ADDRESS),'\0');
	EEPROM_writeByte(IS_IT_FIRST_TIME_ADDRESS,0x00);
}

uint8 isItFirstTime(){
	//uint8 i=0;
	EEPROM_readByte(IS_IT_FIRST_TIME_ADDRESS,&IsItFirstTime);



//	/***************************DEBUGGING SECTION****************************/
//
//	LCD_clearScreen();
//	LCD_displayString("Stuck here #5");
////	_delay_ms(2000);
//
//	/*=====================================================================*/



	if(IsItFirstTime==0xFF){
		EEPROM_writeByte(IS_IT_FIRST_TIME_ADDRESS,0x01);



//		/***************************DEBUGGING SECTION****************************/
//
//		LCD_clearScreen();
//		LCD_displayString("Stuck here #6");
//		_delay_ms(2000);
//
//		/*=====================================================================*/



		UART_sendByte(GET_PASSWORD_FIRST_TIME);



//		/***************************DEBUGGING SECTION****************************/
//
//		LCD_clearScreen();
//		LCD_displayString("Stuck here #7");
////		_delay_ms(2000);
//
//		/*=====================================================================*/




		createNewPassword();

		return 1;

	}else{
//		/***************************DEBUGGING SECTION****************************/
//
//		LCD_clearScreen();
//		LCD_displayString("Stuck here #10");
//	//	_delay_ms(2000);
//
//		/*=====================================================================*/

//		for(i=0; i<PASSWORD_LENGTH; i++){
//			EEPROM_readByte(PASSWORD_FIRST_ADDRESS+i,&SavedPasswordEEPROM[i]);
//		}

		UART_sendByte(GET_PASSWORD);
		UART_recieveString(InputPassword);

		if(passwordChecker()){
			NumberOfFalseTrials=0;
			UART_sendByte(CORRECT_PASSWORD);
			return 1;
		}else{
			UART_sendByte(WRONG_PASSWORD);
			return 0;

		}
	}
}

uint8 passwordChecker(){
	uint8 i=0;
	uint8 NumberOfCorrectMatches=0;
	for(i=0; i<PASSWORD_LENGTH; i++){
		if(SavedPasswordEEPROM[i]==InputPassword[i]){
			NumberOfCorrectMatches++;
		}
	}
	if(NumberOfCorrectMatches==6){
		NumberOfFalseTrials=0;
		return 1;
	}else{
		NumberOfFalseTrials++;
		return 0;
	}
}

void buzzerFor1Min(){
	SET_BIT(DDRD,PD4);
	SET_BIT(PORTD,PD4);
	UART_sendByte(ALARM);
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
	CLEAR_BIT(PORTD,PD4);
}

int main(void){
	uint8 i=0;
	uint8 PasswordStatus;
	uint8 MenuChoice;

	Tconfig.TimerCompareValue=0;
	Tconfig.TimerInitialValue=0;
	Tconfig.TimerMode=0;
	Tconfig.TimerPrescaler=1024;



	SET_BIT(SREG,7);

	UARTconfig.BaudRate=9600;
	UARTconfig.DataBitsLength=8;
	UARTconfig.NumOfStopBits=1;
	UARTconfig.ParityType=2;
	UART_init(&UARTconfig);

	I2Cconfig.Address=1;
	I2Cconfig.BitRate=400000;
	TWI_init(&I2Cconfig);

	EEPROM_init(&I2Cconfig);


	for(i=0; i<PASSWORD_LENGTH; i++){
		EEPROM_readByte(PASSWORD_FIRST_ADDRESS+i,&SavedPasswordEEPROM[i]);
	}



//	/***************************DEBUGGING SECTION****************************/
//
//	LCD_clearScreen();
//	LCD_displayString("Stuck here #1");
////	_delay_ms(2000);
//
//	/*=====================================================================*/

	PasswordStatus=isItFirstTime();

//	/***************************DEBUGGING SECTION****************************/
//
//	LCD_clearScreen();
//	LCD_displayString("Stuck here #2");
////	_delay_ms(2000);
//
//	/*=====================================================================*/

    while(1){
    	if(!PasswordStatus){
    		UART_sendByte(GET_PASSWORD);
    		UART_recieveString(InputPassword);
    		if(passwordChecker()){
    			PasswordStatus=1;
    		}
    	}else{
//    		/***************************DEBUGGING SECTION****************************/
//
//    		LCD_clearScreen();
//    		LCD_displayString("Stuck here #3");
////    		_delay_ms(2000);
//
//    		/*=====================================================================*/

    		UART_sendByte(DISPLAY_MENU);
    		MenuChoice=UART_recieveByte();
    		if(MenuChoice==LOCK_THE_DOOR){
    			TIMER_setCallBack(timerRoutine);
    			TIMER_init(&Tconfig);
    			motorClockWise();

    		}else if(MenuChoice==RESET_PASSWORD){
    			createNewPassword();
    		}

//    		/***************************DEBUGGING SECTION****************************/
//
//    		LCD_clearScreen();
//    		LCD_displayString("Stuck here #4");
////    		_delay_ms(2000);
//
//    		/*=====================================================================*/
    	}

    	if(NumberOfFalseTrials==3){
    		NumberOfFalseTrials=0;
    		buzzerFor1Min();
    	}
    }
}




