/*
 * lcd.c
 *
 *  Created on: Jul 20, 2021
 *      Author: Kirollos
 */

#include "lcd.h"



void LCD_sendCommand(uint8 command){
	CLEAR_BIT(LCD_CONFIG_PORT,RS);
	CLEAR_BIT(LCD_CONFIG_PORT,RW);
	_delay_ms(1);
	SET_BIT(LCD_CONFIG_PORT,E);
	_delay_ms(1);
	LCD_DATA_PORT=command;
	_delay_ms(1);
	CLEAR_BIT(LCD_CONFIG_PORT,E);
	_delay_ms(1);
}

void LCD_init(void){
	LCD_DATA_DDR=0xFF;
	LCD_CONFIG_DDR |= (1<<RW) | (1<<RS) | (1<<E);

	LCD_sendCommand(TWO_LINES_5x8_MATRIX_MODE);
	LCD_sendCommand(CURSOR_OFF);
	LCD_sendCommand(CLEAR_DISPLAY);


}

void LCD_clearScreen(void){
	LCD_sendCommand(CLEAR_DISPLAY);

}

void LCD_displayCharacter(uint8 letter){

	SET_BIT(LCD_CONFIG_PORT,RS);
	CLEAR_BIT(LCD_CONFIG_PORT,RW);
	_delay_ms(1);
	SET_BIT(LCD_CONFIG_PORT,E);
	_delay_ms(1);
	LCD_DATA_PORT=letter;
	_delay_ms(1);
	CLEAR_BIT(LCD_CONFIG_PORT,E);
	_delay_ms(1);

}

void LCD_displayString(const int8 *str){
	uint8 i=0;
	for(i=0; str[i] != '\0'; i++){
		LCD_displayCharacter(str[i]);
	}
}

void LCD_goToRowColumn(uint8 row,uint8 column){
	uint8 Address;
	switch(row){
	case 0:
		Address=column;
		break;
	case 1:
		Address=column + 0x40;
		break;
	case 2:
		Address=column + 0x10;
		break;
	case 3:
		Address=column + 0x50;
		break;
	}
	LCD_sendCommand(Address|SET_CURSOR_LINE_ONE);
}

void LCD_displayStringRowColumn(uint8 row,uint8 column,int8 *str){
	LCD_goToRowColumn(row,column);
	LCD_displayString(str);
}

void LCD_integerToString(int Data){
	int8 str[16 ];
	itoa(Data,str,10);
	LCD_displayString(str);
}
