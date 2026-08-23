/*
 * EEPROM.h
 *
 *  Created on: Jul 21, 2021
 *      Author: Kirollos
 */

#ifndef EEPROM_H_
#define EEPROM_H_

#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"
#include "i2c.h"

void EEPROM_init(struct I2CConfiguration *);
uint8 EEPROM_writeByte(uint16,uint8);
uint8 EEPROM_readByte(uint16,uint8*);

#endif /* EEPROM_H_ */
