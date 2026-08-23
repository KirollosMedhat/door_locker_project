/*
 * i2c.h
 *
 *  Created on: Jul 21, 2021
 *      Author: Kirollos
 */

#ifndef I2C_H_
#define I2C_H_

#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"

struct I2CConfiguration{
	uint8 Address;
	uint32 BitRate;
}I2Cconfig;

#define START_CONDITION_SENT 0x08
#define REPEATED_START_SENT 0x10
#define MT_SA_W_ACK 0x18			/*Master transmit slave address write acknowledge recieved*/
#define MT_SA_R_ACK 0x40			/*Master transmit slave address read acknowledge recieved*/
#define MT_DATA_ACK 0x28			/*Master trasmit data acknowledge recieved*/
#define MR_DATA_ACK 0x50			/*Master recieve data acknowledge recieved*/
#define MR_DATA_NACK 0x058			/*Master recieve data and no acknowledge  sent back*/

void TWI_init(struct I2CConfiguration *);
void TWI_start(void);
void TWI_stop(void);
void TWI_write(uint8 data);
uint8 TWI_readWithACK(void);
uint8 TWI_readWithNACK(void);
uint8 TWI_getStatus(void);

#endif /* I2C_H_ */
