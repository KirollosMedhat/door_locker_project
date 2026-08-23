/*
 * timers.c
 *
 *  Created on: Jul 22, 2021
 *      Author: Kirollos
 */

#include "timers.h"

ISR(TIMER0_COMP_vect){
	(*callBackPtr)();
}

ISR(TIMER0_OVF_vect){
	(*callBackPtr)();
}

void TIMER_setCallBack(void(*ptrToFunc)(void)){
	callBackPtr=ptrToFunc;

}

void TIMER_init(struct TimerConfiguration *ptr){
	if(ptr->TimerMode==0){								/*Normal Mode*/
		TCCR0|=(1<<FOC0);
		TCNT0=ptr->TimerInitialValue;					/*Initial Value*/
		TIMSK|=(1<<TOIE0);
	}else if(ptr->TimerMode==1){						/*Compare Mode*/
		TCCR0|=(1<<FOC0)|(1<<WGM01);
		TCNT0=ptr->TimerInitialValue;					/*Initial Value*/
		OCR0=ptr->TimerCompareValue;					/*Compare Value*/
		TIMSK|=(1<<OCIE0);
	}

	if(ptr->TimerPrescaler==0){
		TCCR0|=(1<<CS00);
	}else if(ptr->TimerPrescaler==8){
		TCCR0|=(1<<CS01);
	}else if(ptr->TimerPrescaler==64){
		TCCR0|=(1<<CS00)|(1<<CS01);
	}else if(ptr->TimerPrescaler==256){
		TCCR0|=(1<<CS02);
	}else if(ptr->TimerPrescaler==1024){
		TCCR0|=(1<<CS02)|(1<<CS00);
	}
}

void TIMER_stop(void){
	CLEAR_BIT(TCCR0,CS02);
	CLEAR_BIT(TCCR0,CS01);
	CLEAR_BIT(TCCR0,CS00);
}
