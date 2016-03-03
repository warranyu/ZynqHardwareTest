/*
 * adv7511.c

 *
 *  Created on: Nov 10, 2013
 *      Author: jdecesare
 */
#include <stdio.h>
#include "uart.h"
#include "cli.h"
#include "ctypes.h"
#include "ADV7611.h"
#include "ADV7611_config.h"

#include "gpio/GpioController.h"
#include "i2c/I2cController.h"

static char adv7611_command[] = "adv7611";
static void adv7611_cli(char *parms);

uint16_t ADV7611_GetID(uint8_t bus_num, uint8_t device_num)
{
	uint8_t idL = 0;
	uint8_t idH = 0;
	uint16_t id = 0;
	uint8_t buff[1];
	char str[100];

	buff[0] = ADV7611_CHIP_ID_HIGH_ADDR;
	I2cController_Write(bus_num, device_num, buff, 1, 0);
	I2cController_Read(bus_num, device_num, &idH, 2, 1);

	buff[0] = ADV7611_CHIP_ID_LOW_ADDR;
	I2cController_Write(bus_num, device_num, buff, 1, 0);
	I2cController_Read(bus_num, device_num, &idL, 2, 1);

	id = (idH << 8) + idL;
	sprintf(str,"\tExpecting Device ID of 0x%04X. Got 0x%04X\n\r", ADV7611_CHIP_ID,id);

	Cli_print(str);
	return(id);
}

void ADV7611_Reset(bool active)
{
	if(active)
	{
		GpioController_SetVal(ADV7611_DEV1_GPIO_RST, 0);
	}
	else
		GpioController_SetVal(ADV7611_DEV1_GPIO_RST, 1);
}

bool ADV7611_SelfTest()
{
	bool pass = true;
#ifdef ADV7611_DEV1
	if(ADV7611_GetID(ADV7611_DEV1_I2C_BUS, ADV7611_DEV1_I2C_BUS_DEVICE_NUM) != ADV7611_CHIP_ID)
		pass = false;
#endif
	return pass;
}

void ADV7611_registerWrite(uint8_t bus_num, uint8_t device_num, uint8_t reg, uint8_t val)
{
	uint8_t buff[2];

	buff[0] = reg;
	buff[1] = val;
	I2cController_Write(bus_num, device_num, buff, 2, 1);
}

static void ADV7611_RstDelay(u32 delay)
{
	u8 d;
	while(delay--)
	{
		d = 0xff;
		while(d--);
	}
}

void ADV7611_Initialize(uint8_t bus_num, uint8_t device_num)
{

	GpioController_SetDir(ADV7611_DEV1_GPIO_RST, 1);
	GpioController_SetOutputEn(ADV7611_DEV1_GPIO_RST, 1);

	ADV7611_Reset(true);
	ADV7611_RstDelay(0x2000);
	ADV7611_Reset(false);
}

void ADV7611_Init(void)
{
	S_CLI cli;

	cli.cli = (PFV_S)adv7611_cli;
	cli.command = adv7611_command;
	cli_install(&cli);


#ifdef ADV7611_DEV1
	I2cController_AddDevice(ADV7611_DEV1_I2C_BUS, ADV7611_DEV1_I2C_ADDR, ADV7611_DEV1_I2C_BUS_DEVICE_NUM, 0, 0);
	ADV7611_Initialize(ADV7611_DEV1_I2C_BUS, ADV7611_DEV1_I2C_BUS_DEVICE_NUM);
#endif
}

static void adv7611_cli(char *parms)
{
	uint8_t cmd;

	sscanf(parms,"%1c",&cmd);

	switch(cmd)
	{
	case 't':
		ADV7611_SelfTest();
		break;

	default:
		Cli_print("\n\rADV7611 t - Performs self test on the ADV7611");
		Cli_print("\n\rADV7611 ? - Displays this help message");
		break;
	}
}



