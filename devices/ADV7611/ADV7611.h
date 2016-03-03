/*
 * ADV7611.h
 *
 *  Created on: Nov 10, 2013
 *      Author: jdecesare
 */
#ifndef ADV7611_H
#define ADV7611_H

#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xparameters.h"
#include "uart.h"
#include <stdint.h>
#include <stdbool.h>

#define ADV7611_CHIP_ID_LOW_ADDR 0xEB
#define ADV7611_CHIP_ID_HIGH_ADDR 0xEA

#define ADV7611_CHIP_ID_LOW 0x51
#define ADV7611_CHIP_ID_HIGH 0x20
#define ADV7611_CHIP_ID ((ADV7611_CHIP_ID_HIGH<<8) + ADV7611_CHIP_ID_LOW)

void ADV7611_Init(void);
bool ADV7611_SelfTest();
uint16_t ADV7611_GetID(uint8_t bus_num, uint8_t device_num);

#endif // ADV7611_H


