/*
 * keypad.h
 *
 *  Created on: Jul 19, 2021
 *      Author: Kirollos
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_


#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"

#define KEYPAD_PORT PORTA
#define KEYPAD_PIN PINA
#define KEYPAD_DDR DDRA

#define NUM_OF_COLUMNS 4             /*3 For 4x3 Keypads, 4 for 4x4 Keypads)*/
#define NUM_OF_ROWS 4

uint8 Keypad_getPressedKey(void);
#endif /* KEYPAD_H_ */
