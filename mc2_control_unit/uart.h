/*
 * uart.h
 *
 *  Created on: Jul 20, 2021
 *      Author: Kirollos
 */

#ifndef UART_H_
#define UART_H_

#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"

struct UARTConfiguration{
	uint8 DataBitsLength;
	uint8 NumOfStopBits;
	uint8 ParityType;			/*ParityType=0 for even parity, ParityType=1 for odd parity*/
	uint32 BaudRate;
}UARTconfig;

//#define UART_BAUDRATE 9600
#define BAUD_PRESCALE_DOUBLE_SPEED (( F_CPU / ((ptr->BaudRate)*8UL) )-1)
#define BAUD_PRESCALE_NORMAL_SPEED (( F_CPU / (ptr->BaudRate*16UL) )-1)

void UART_init(struct UARTConfiguration *);
void UART_sendByte(const uint8);
uint8 UART_recieveByte(void);
void UART_sendString(const uint8 *);
void UART_recieveString(uint8 *);

#endif /* UART_H_ */
