/*
 * keypad.c
 *
 *  Created on: Jul 19, 2021
 *      Author: Kirollos
 */
#include "keypad.h"

#if(NUM_OF_COLUMNS==3)
static uint8 Keypad_4x3_adjustKeyNumber(uint8 ButtonNumber);
#elif(NUM_OF_COLUMNS==4)
static uint8 Keypad_4x4_adjustKeyNumber(uint8 ButtonNumber);
#endif

uint8 Keypad_getPressedKey(void){
	uint8 rows=0,cols=0;
	while(1){
		for(cols=0; cols<NUM_OF_COLUMNS; cols++){

			KEYPAD_DDR=(0b00010000<<cols); /*set columns(pins in the port) as an output one at a time*/

			KEYPAD_PORT=(~(0b00010000<<cols)); /* activate pull-up resistance for all other input pins
			 	 	 	 	 	 	 	 	 	 and set the output value of the activated
			 	 	 	 	 	 	 	 	 	 (the pin used as output) pin to 0*/
			for(rows=0;rows<NUM_OF_ROWS;rows++){
				if( BIT_IS_CLEAR(KEYPAD_PIN,rows) ){
					_delay_ms(500);
					#if(NUM_OF_COLUMNS==3)
					return Keypad_4x3_adjustKeyNumber((rows*NUM_OF_COLUMNS)+cols+1);
					#elif(NUM_OF_COLUMNS==4)
					return Keypad_4x4_adjustKeyNumber((rows*NUM_OF_COLUMNS)+cols+1);
					#endif
				}
			}
		}
	}
}
#if(NUM_OF_COLUMNS==3)
static uint8 Keypad_4x3_adjustKeyNumber(uint8 ButtonNumber){
	switch(ButtonNumber){
	case 10:
		return '*';
		break;
	case 11:
		return 0;
		break;
	case 12:
		return '#';
		break;
	default:
		return ButtonNumber;
	}
}


#elif(NUM_OF_COLUMNS==4)
static uint8 Keypad_4x4_adjustKeyNumber(uint8 ButtonNumber){
	switch(ButtonNumber){
	case 1:
		return 7;
		break;
	case 2:
		return 8;
		break;
	case 3:
		return 9;
		break;
	case 4:
		return '%';
		break;
	case 5:
		return 4;
		break;
	case 6:
		return 5;
		break;
	case 7:
		return 6;
		break;
	case 8:
		return '*';
		break;
	case 9:
		return 1;
		break;
	case 10:
		return 2;
		break;
	case 11:
		return 3;
		break;
	case 12:
		return '-';
		break;
	case 13:
		return 13;
		break;
	case 14:
		return 0;
		break;
	case 15:
		return '=';
		break;
	case 16:
		return '+';
		break;
	default:
		return ButtonNumber;
	}
}
#endif
