/*
 * ADV7511.h
 *
 *  Created on: Nov 10, 2013
 *      Author: jdecesare
 */
#ifndef ADV7511_H
#define ADV7511_H

#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xparameters.h"
#include "uart.h"
#include <stdint.h>
#include <stdbool.h>

typedef enum {ADV7511_1=1, ADV7511_2=2,ADV7511_3=3,ADV7511_4=4} ADV7511_DEV;

#define ADV7511_CHIP_ID_LOW 0x11
#define ADV7511_CHIP_ID_HIGH 0x75
#define ADV7511_CHIP_ID ((ADV7511_CHIP_ID_HIGH<<8) +ADV7511_CHIP_ID_LOW)

void ADV7511_Init(void);
bool ADV7511_SelfTest();
uint16_t ADV7511_GetID(uint8_t bus_num, uint8_t device_num);

#endif // ADV7511_H


