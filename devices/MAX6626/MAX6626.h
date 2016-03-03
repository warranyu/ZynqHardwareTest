/*
 * i2c.h
 *
 *  Created on: Nov 10, 2013
 *      Author: jdecesare
 */
#ifndef MAX6626_H
#define MAX6626_H

#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xparameters.h"

#define MAX6626_REG_TEMP 0x00
#define MAX6626_REG_CONFIG 0x01
#define MAX6626_REG_TLOW 0x02
#define MAX6626_REG_THIGH 0x03

void Init_tempSensors(void);
int32_t MAX6626_ReadTemp(uint8_t bus_num, uint8_t device_num);
int Display_Power_Supply_Temp(void);
int Display_Fiber_Driver_Temp(void);
void MAX6626_Init();



#endif // I2C_H


