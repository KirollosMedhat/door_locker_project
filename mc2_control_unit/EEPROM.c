/*
 * EEPROM.c
 *
 *  Created on: Jul 21, 2021
 *      Author: Kirollos
 */

#include "EEPROM.h"


void EEPROM_init(struct I2CConfiguration *ptr){
	TWI_init(ptr);
}

uint8 EEPROM_writeByte(uint16 address,uint8 data){

	TWI_start();
	if(TWSR!=START_CONDITION_SENT){
		return 0;
	}


	TWI_write((uint8) (0xA0 | ( (address&0x0700) >>7 ) ) );             /*sending the slave device address*/
	if(TWSR!=MT_SA_W_ACK){
		return 0;
	}


	TWI_write( (uint8) (address)); 										/*sending the word address*/
	if(TWSR!=MT_DATA_ACK){
		return 0;
	}


	TWI_write(data);
	if(TWSR!=MT_DATA_ACK){
		return 0;
	}


	TWI_stop();
	return 1;
}

uint8 EEPROM_readByte(uint16 address,uint8 *data){

	TWI_start();
	if(TWSR!=START_CONDITION_SENT){
		return 0;
	}


	TWI_write((uint8) (0xA0 | ( (address&0x0700) >>7 ) ) );             /*sending the slave device address*/
	if(TWSR!=MT_SA_W_ACK){
		return 0;
	}

	TWI_write( (uint8) (address)); 										/*sending the word address*/
	if(TWSR!=MT_DATA_ACK){
		return 0;
	}


	TWI_start();														/*Repeated start bit*/
	if(TWSR!=REPEATED_START_SENT){
		return 0;
	}

	TWI_write((uint8) (0xA0 | ( (address&0x0700) >>7 ) ) | 1 );             /*sending the slave device address*/
	if(TWSR!=MT_SA_R_ACK){
		return 0;
	}

	*data=TWI_readWithNACK();
	if(TWSR!=MR_DATA_NACK){
		return 0;
	}

	TWI_stop();
	return 1;
}
