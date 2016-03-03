/*
 * i2C.c

 *
 *  Created on: Nov 10, 2013
 *      Author: jdecesare
 */
#include <stdio.h>
#include "MAX6626.h"
#include "cli.h"
#include "i2c/I2cController.h"
#include "MAX6626_config.h"

#ifdef MAX6626_CLI
static char temp_command[] = "max6626";
static void temp_cli(char *parms);

static void temp_cli(char *parms)
{
	Display_Power_Supply_Temp();
	Display_Fiber_Driver_Temp();
}

#endif

void MAX6626_WriteReg(uint8_t bus_num, uint8_t device_num,u8 reg,u8 val)
{
	u8 buff[2];

	buff[0] = reg;
	buff[1] = val;

	I2cController_Write(bus_num, device_num, buff, 2, 1);
}

static void MAX6626_WriteConfigReg(uint8_t bus_num, uint8_t device_num, uint8_t data)
{

	MAX6626_WriteReg(bus_num, device_num ,MAX6626_REG_CONFIG, data);
}

int Display_Power_Supply_Temp(void)
{
	char str[64];
	int temp;

	temp = MAX6626_ReadTemp(MAX6626_DEV1_I2C_BUS, MAX6626_DEV1_I2C_BUS_DEVICE_NUM);

	sprintf(str,"\tPower Supply Temp: %d C\n\r", temp);
	print(str);

	return temp;
}

int Display_Fiber_Driver_Temp(void)
{
	char str[64];
	int temp;

	temp = MAX6626_ReadTemp(MAX6626_DEV2_I2C_BUS, MAX6626_DEV1_I2C_BUS_DEVICE_NUM);

	sprintf(str,"\tFiber Driver Temp: %d C\n\r", temp);
	print(str);

	return temp;
}



uint16_t MAX6626_ReadReg(uint8_t bus_num, uint8_t device_num, uint8_t regaddr)
{
	u8 buff[2];
	uint16_t val;

	I2cController_Write(bus_num, device_num, &regaddr, 1, 0);
	I2cController_Read(bus_num, device_num, buff, 2, 1);

	val = buff[0];
	val <<= 8;
	val += buff[1];

	return val;
}

int32_t MAX6626_ReadTemp(uint8_t bus_num, uint8_t device_num)
{
	u32 temp;
	s32 retval;

	u8 neg = 0;

	temp = MAX6626_ReadReg(bus_num, device_num, MAX6626_REG_TEMP);

	if (temp & 0x8000) neg = 1;
	temp &= 0x7FFF;
	temp >>=4;

	temp *= 625;	// each bit is 0.0625V
	temp /= 10000;

	retval = (s32)temp;
	if (neg) retval *= -1;

	return(temp);
}


void MAX6626_Init()
{
#ifdef MAX6626_CLI
	S_CLI cli;

	cli.cli = (PFV_S)temp_cli;
	cli.command = temp_command;
	cli_install(&cli);
#endif

#ifdef MAX6626_DEV1
	I2cController_AddDevice(MAX6626_DEV1_I2C_BUS, MAX6626_DEV1_I2C_ADDR, MAX6626_DEV1_I2C_BUS_DEVICE_NUM, 0, 0);
	MAX6626_WriteConfigReg(MAX6626_DEV1_I2C_BUS, MAX6626_DEV1_I2C_BUS_DEVICE_NUM, 0);
#endif

#ifdef MAX6626_DEV2
	I2cController_AddDevice(MAX6626_DEV2_I2C_BUS, MAX6626_DEV2_I2C_ADDR, MAX6626_DEV2_I2C_BUS_DEVICE_NUM, 0, 0);
	MAX6626_WriteConfigReg(MAX6626_DEV2_I2C_BUS, MAX6626_DEV2_I2C_BUS_DEVICE_NUM, 0);
#endif
}
