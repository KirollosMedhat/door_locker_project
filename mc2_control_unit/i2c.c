/*
 * i2c.c
 *
 *  Created on: Jul 21, 2021
 *      Author: Kirollos
 */

#include "i2c.h"

void TWI_init(struct I2CConfiguration *ptr){
	TWSR=0x00;     /*prescaler*/
	TWBR=((F_CPU/(ptr->BitRate))-16)/2;
	TWAR=(ptr->Address)<<1;         /*Address*/
	TWCR=(1<<TWEN);     /*enabling TWI interface*/
}

void TWI_start(void){
	TWCR=(1<<TWINT) | (1<<TWSTA) | (1<<TWEN);

	while(BIT_IS_CLEAR(TWCR,TWINT)){

	}
}

void TWI_stop(void){
	TWCR=(1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}

void TWI_write(uint8 data){

	TWDR=data;

	TWCR=(1<<TWINT)|(1<<TWEN);

	while(BIT_IS_CLEAR(TWCR,TWINT)){

	}
}

uint8 TWI_readWithACK(void){
	TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA);

	while(BIT_IS_CLEAR(TWCR,TWINT)){

		}
	return TWDR;
}

uint8 TWI_readWithNACK(void){
	TWCR=(1<<TWINT)|(1<<TWEN);

	while(BIT_IS_CLEAR(TWCR,TWINT)){

	}
	return TWDR;
}

uint8 TWI_getStatus(void){
	return (TWSR&0xF8);
}
