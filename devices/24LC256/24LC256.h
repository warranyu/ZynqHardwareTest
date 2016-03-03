/*
 * File:   EEPROM_24LC256.h
 * Author: wwalton
 *
 * Created on July 2, 2014, 10:57 AM
 */

#ifndef EEPROM_24LC256_H
#define	EEPROM_24LC256_H

#include <stdint.h>
#include <stdbool.h>

void EEPROM_24LC256_init();
void EEPROM_24LC256_WriteByte(uint16_t reg, uint8_t data);
uint8_t EEPROM_24LC256_ReadByte(uint16_t reg);
void EEPROM_24LC256Test_init();
bool EEPROM_24LC256_self_test();
#endif	/* EEPROM_24LC256_H */

