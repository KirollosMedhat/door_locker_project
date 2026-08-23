/*
 * timers.h
 *
 *  Created on: Jul 22, 2021
 *      Author: Kirollos
 */

#ifndef TIMERS_H_
#define TIMERS_H_

#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"

volatile void (*callBackPtr)(void);			/*Global pointer to function*/

struct TimerConfiguration{					/*TimerNumber = 0 for timer0*/  /*TimerMode = 0 for normal mode*/
//	uint8 TimerNumber;						/*TimerNumber = 1 for timer1*/  /*TimerMode = 1 for comparison mode*/
	uint8 TimerMode;						/*TimerNumber = 2 for timer2*/
	uint8 TimerInitialValue;				/**/
	uint8 TimerCompareValue;				/**/
	uint16 TimerPrescaler;					/*0 for no prescaler*/
	/*TimerCompareValue can take any value when running on normal mode*/
}Tconfig;

/* This Driver is for Timer0 only therefore:
 *
 * TimerInitialValue and TimerCompareValue
 * Cannot exceed 254 for Timer0
 *
 */

/* TimerPrescaler can be:
 * 0
 * 8
 * 64
 * 256
 * 1024
 */

void TIMER_init(struct TimerConfiguration *);
void TIMER_stop(void);
void TIMER_setCallBack(void(*ptrToFunc)(void));



#endif /* TIMERS_H_ */
