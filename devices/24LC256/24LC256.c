#include "EEPROM_24LC256_config.h"
#include "EEPROM_24LC256.h"
#include "i2c/I2cController.h"
#include "gpio/GpioController.h"
//#include "system.h"
#include <stdbool.h>
#include <stdlib.h>
#include "cli.h"
#include "uart.h"
#include <stdio.h>
#if defined(EEPROM_24LC256_DEV1)
#endif
#if defined(EEPROM_24LC256_DEV2)
i2c_device_t * EEPROM_24LC256_dev2_i2c;
#endif


#if defined(EEPROM_24LC256_CLI_TEST)
#include "cli.h"

static char EEPROM_24LC256_test_cmd[] = "EEPROM_24LC256-test";
static void EEPROM_24LC256_test(char *parms);

void EEPROM_24LC256Test_init()
{
    // install CLI command
    S_CLI cli;

    cli.cli = (PFV_S)EEPROM_24LC256_test;
    cli.command = EEPROM_24LC256_test_cmd;
    cli_install(&cli);
}

static void EEPROM_24LC256_test(char *parms)
{
	// Todo
}
#endif

static void EEPROM_Write_Delay(u32 delay)
{
	u8 d;
	while(delay--)
	{
		d = 0xff;
		while(d--);
	}
}

void EEPROM_24LC256_WriteProtect(uint8_t on)
{
	if(on)
	{
		GpioController_SetVal(EEPROM_24LC256_DEV1_GPIO_WP, 1);
	}
	else
		GpioController_SetVal(EEPROM_24LC256_DEV1_GPIO_WP, 0);
}


void EEPROM_24LC256_WriteByte(uint16_t reg, uint8_t data)
{
	uint8_t buff[3];

	buff[0] = (uint8_t)(reg<<8);
	buff[1] = (uint8_t)(reg<<0);
	buff[2] = data;
	I2cController_Write(EEPROM_24LC256_DEV1_I2C_BUS, EEPROM_24LC256_DEV1_I2C_BUS_DEVICE_NUM, buff, 3, 1);
    return;
}

uint8_t EEPROM_24LC256_ReadByte(uint16_t reg)
{
	uint8_t buff[2],val;

	buff[0] = (uint8_t)(reg<<8);
	buff[1] = (uint8_t)(reg<<0);
	I2cController_Write(EEPROM_24LC256_DEV1_I2C_BUS, EEPROM_24LC256_DEV1_I2C_BUS_DEVICE_NUM, buff, 2, 0);
	EEPROM_Write_Delay(0x2000);
	I2cController_Read(EEPROM_24LC256_DEV1_I2C_BUS, EEPROM_24LC256_DEV1_I2C_BUS_DEVICE_NUM, &val, 1, 1);

    return val;
}

bool EEPROM_24LC256_self_test()
{
	uint8_t val;
	bool pass = true;
	char str[16];

	// Disable Write Protect
	Cli_print("\tTesting EEPROM (WP=0)...Wrote 0x00..");
	EEPROM_24LC256_WriteProtect(0);
	EEPROM_24LC256_WriteByte(0, 0);
	EEPROM_Write_Delay(0x2000);
	val = EEPROM_24LC256_ReadByte(0);
	sprintf(str,"Read 0x%02x\n\r",val);
	Cli_print(str);
	if (val != 0)
		pass = false;

	Cli_print("\tTesting EEPROM (WP=0)...Wrote 0xaa..");
	EEPROM_24LC256_WriteByte(0, 0xAA);
	EEPROM_Write_Delay(0x2000);
	val = EEPROM_24LC256_ReadByte(0);
	sprintf(str,"Read 0x%02x\n\r",val);
	Cli_print(str);
	if (val != 0xAA)
		pass = false;

	Cli_print("\tTesting EEPROM (WP=1)...Wrote 0x00..");
	EEPROM_24LC256_WriteProtect(1);
	EEPROM_24LC256_WriteByte(0, 0);
	EEPROM_Write_Delay(0x2000);
	val = EEPROM_24LC256_ReadByte(0);
	sprintf(str,"Read 0x%02x\n\r",val);
	Cli_print(str);
	if (val != 0xAA)
		pass = false;

	return pass;
}

void EEPROM_24LC256_setup()
{
	// Todo
}

void EEPROM_24LC256_init()
{
	GpioController_SetDir(EEPROM_24LC256_DEV1_GPIO_WP, 1);
	GpioController_SetOutputEn(EEPROM_24LC256_DEV1_GPIO_WP, 1);
	I2cController_AddDevice(EEPROM_24LC256_DEV1_I2C_BUS, EEPROM_24LC256_DEV1_I2C_ADDR, EEPROM_24LC256_DEV1_I2C_BUS_DEVICE_NUM, EEPROM_24LC256_DEV1_I2C_CLK, EEPROM_24LC256_DEV1_I2C_TIMEOUT);
}


