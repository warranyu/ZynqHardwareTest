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
#include "ADV7511.h"
#include "ADV7511_config.h"

#include "i2c/I2cController.h"


static char adv7511_command[] = "adv7511";
static void adv7511_cli(char *parms);

static void ADV7511_Delay(uint32_t delay)
{
	uint8_t d;
	while(delay--)
	{
		d = 0xff;
		while(d--);
	}
}

uint16_t ADV7511_GetID(uint8_t bus_num, uint8_t device_num)
{
	uint8_t idL;
	uint8_t idH;
	uint16_t id;
	uint8_t buff[1];
	char str[100];

	buff[0] = 0xF5;
	I2cController_Write(bus_num, device_num, buff, 1, 0);
	I2cController_Read(bus_num, device_num, &idH, 2, 1);

	buff[0] = 0xF6;
	I2cController_Write(bus_num, device_num, buff, 1, 0);
	I2cController_Read(bus_num, device_num, &idL, 2, 1);

	id = (idH << 8) + idL;
	sprintf(str,"\tExpecting Device ID of 0x%04X. Got 0x%04X\n\r", ADV7511_CHIP_ID,id);

	Cli_print(str);
	return(id);
}

bool ADV7511_SelfTest()
{
	bool pass = true;
#ifdef ADV7511_DEV1
	if(ADV7511_GetID(ADV7511_DEV1_I2C_BUS, ADV7511_DEV1_I2C_BUS_DEVICE_NUM) != ADV7511_CHIP_ID)
		pass = false;
#endif

#ifdef ADV7511_DEV2
	if(ADV7511_GetID(ADV7511_DEV2_I2C_BUS, ADV7511_DEV2_I2C_BUS_DEVICE_NUM) != ADV7511_CHIP_ID)
		pass = false;
#endif

#ifdef ADV7511_DEV3
	if(ADV7511_GetID(ADV7511_DEV3_I2C_BUS, ADV7511_DEV3_I2C_BUS_DEVICE_NUM) != ADV7511_CHIP_ID)
		pass = false;
#endif

#ifdef ADV7511_DEV4
	if(ADV7511_GetID(ADV7511_DEV4_I2C_BUS, ADV7511_DEV4_I2C_BUS_DEVICE_NUM) != ADV7511_CHIP_ID)
		pass = false;
#endif

	return pass;
}

void ADV7511_registerWrite(uint8_t bus_num, uint8_t device_num, uint8_t reg, uint8_t val)
{
	uint8_t buff[2];

	buff[0] = reg;
	buff[1] = val;
	I2cController_Write(bus_num, device_num, buff, 2, 1);
	ADV7511_Delay(200);
}

void ADV7511_Adv7511_Initialize(uint8_t bus_num, uint8_t device_num)
{
	ADV7511_registerWrite(bus_num, device_num, 0x98,0x03);
	ADV7511_registerWrite(bus_num, device_num, 0x9A,0xE0);
	ADV7511_registerWrite(bus_num, device_num, 0x9C,0x30);
	ADV7511_registerWrite(bus_num, device_num, 0x9D,0x01);
	ADV7511_registerWrite(bus_num, device_num, 0xA2,0xA4);
	ADV7511_registerWrite(bus_num, device_num, 0xA3,0xA4);
	ADV7511_registerWrite(bus_num, device_num, 0xE0,0xD0);
	ADV7511_registerWrite(bus_num, device_num, 0xF9,0x00);
}

void ADV7511_Init(void)
{
	S_CLI cli;

	cli.cli = (PFV_S)adv7511_cli;
	cli.command = adv7511_command;
	cli_install(&cli);


#ifdef ADV7511_DEV1
	I2cController_AddDevice(ADV7511_DEV1_I2C_BUS, ADV7511_DEV1_I2C_ADDR, ADV7511_DEV1_I2C_BUS_DEVICE_NUM, 0, 0);
	ADV7511_Adv7511_Initialize(ADV7511_DEV1_I2C_BUS, ADV7511_DEV1_I2C_BUS_DEVICE_NUM);
#endif

#ifdef ADV7511_DEV2
	I2cController_AddDevice(ADV7511_DEV2_I2C_BUS, ADV7511_DEV1_I2C_ADDR, ADV7511_DEV2_I2C_BUS_DEVICE_NUM, 0, 0);
	ADV7511_Adv7511_Initialize(ADV7511_DEV2_I2C_BUS, ADV7511_DEV2_I2C_BUS_DEVICE_NUM);
#endif

#ifdef ADV7511_DEV3
	I2cController_AddDevice(ADV7511_DEV3_I2C_BUS, ADV7511_DEV1_I2C_ADDR, ADV7511_DEV3_I2C_BUS_DEVICE_NUM, 0, 0);
	ADV7511_Adv7511_Initialize(ADV7511_DEV3_I2C_BUS, ADV7511_DEV3_I2C_BUS_DEVICE_NUM);
#endif

#ifdef ADV7511_DEV4
	I2cController_AddDevice(ADV7511_DEV4_I2C_BUS, ADV7511_DEV1_I2C_ADDR, ADV7511_DEV4_I2C_BUS_DEVICE_NUM, 0, 0);
	ADV7511_Adv7511_Initialize(ADV7511_DEV4_I2C_BUS, ADV7511_DEV4_I2C_BUS_DEVICE_NUM);
#endif
}

static void adv7511_cli(char *parms)
{
	uint8_t cmd;

	sscanf(parms,"%1c",&cmd);

	switch(cmd)
	{
	case 't':
		ADV7511_SelfTest();
		break;

	default:
		Cli_print("\n\rADV7511 t - Performs self test on ADV7511\'s");
		Cli_print("\n\rADV7511 ? - Displays this help message");
		break;
	}
}


