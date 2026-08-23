/*
 * lcd.h
 *
 *  Created on: Jul 20, 2021
 *      Author: Kirollos
 */

#ifndef LCD_H_
#define LCD_H_

#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"



void LCD_sendCommand(uint8 command);
void LCD_displayCharacter(uint8 letter);
void LCD_displayString(const int8 *str);
void LCD_init(void);
void LCD_clearScreen(void);
void LCD_displayStringRowColumn(uint8 row,uint8 column,int8*);
void LCD_goToRowColumn(uint8 row,uint8 column);
void LCD_integerToString(int Data);



/*Commands*/

#define CLEAR_DISPLAY 0x01
#define CURSOR_OFF 0x0C
#define CURSOR_ON 0x0E
#define TWO_LINES_5x8_MATRIX_MODE 0x38
#define SET_CURSOR_LINE_ONE 0x80
#define SET_CURSOR_LINE_TWO 0xC0

/*Pins*/

#define RS PB4
#define RW PB5
#define E PB6
#define LCD_CONFIG_PORT PORTB
#define LCD_CONFIG_DDR DDRB

#define LCD_DATA_PORT PORTA
#define LCD_DATA_DDR DDRA

//#define RS PD4
//#define RW PD5
//#define E PD6
//#define LCD_CONFIG_PORT PORTD
//#define LCD_CONFIG_DDR DDRD
//
//#define LCD_DATA_PORT PORTC
//#define LCD_DATA_DDR DDRC

#endif /* LCD_H_ */
