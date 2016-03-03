/*
 * mcp79400.c

 *
 *  Created on: Nov 10, 2013
 *      Author: jdecesare
 */
#include <stdio.h>
#include "uart.h"
#include "cli.h"
#include "ctypes.h"
#include "MCP79400.h"
#include "MCP79400_config.h"
#include "gpio/GpioController.h"
#include "i2c/I2cController.h"

#ifdef MCP79400_CLI
static char rtc_command[] = "rtc";
static void rtc_cli(char *parms);

static void rtc_cli(char *parms)
{
	uint8_t cmd;

	sscanf(parms,"%1c",&cmd);

	switch(cmd)
	{
	case 't':
		RTC_SelfTest();
		break;

	default:
		Cli_print("\n\rrtc t - Performs RTC self test.");
		Cli_print("\n\rrtc ? - Displays this help message");
		break;
	}
}

#endif

static void RTC_delay(void)
{
	int x = 0xFFFFF;
	while(x--);
}


void RTC_WriteSRAM(u8 addr,u8 data)
{
	u8 buff[2];
	addr &= (MCP_79400_RAM_SIZE-1);  // keep it between 0 and 63

	buff[0] = MCP_79400_RAM_BASE + addr;
	buff[1] = data;
	I2cController_Write(MCP79400_DEV1_I2C_BUS, MCP79400_DEV1_I2C_BUS_DEVICE_NUM, buff, 2, 1);
}

u8 RTC_ReadSRAM(u8 addr)
{
	u8 buff[2],val;
	addr &= (MCP_79400_RAM_SIZE-1);  // keep it between 0 and 63

	buff[0] = MCP_79400_RAM_BASE + addr;

	I2cController_Write(MCP79400_DEV1_I2C_BUS, MCP79400_DEV1_I2C_BUS_DEVICE_NUM, buff, 1, 0);
	I2cController_Read(MCP79400_DEV1_I2C_BUS, MCP79400_DEV1_I2C_BUS_DEVICE_NUM, &val, 2, 1);
	return(val);
}

void RTC_WriteReg(u8 addr,u8 data)
{
	u8 buff[2];
	addr &= (MCP_79400_REG_SIZE-1);  // keep it between 0 and 63

	buff[0] = MCP_79400_REG_BASE + addr;
	buff[1] = data;
	I2cController_Write(MCP79400_DEV1_I2C_BUS, MCP79400_DEV1_I2C_BUS_DEVICE_NUM, buff, 2, 1);
}

u8 RTC_ReadReg(u8 addr)
{
	u8 buff[1];
	u8 val[1] = {0};
	addr &= (MCP_79400_REG_SIZE-1);  // keep it between 0 and 63

	buff[0] = MCP_79400_REG_BASE + addr;

	I2cController_Write(MCP79400_DEV1_I2C_BUS, MCP79400_DEV1_I2C_BUS_DEVICE_NUM, buff, 1, 0);
	I2cController_Read(MCP79400_DEV1_I2C_BUS, MCP79400_DEV1_I2C_BUS_DEVICE_NUM, val, 2, 1);

	return val[0];
}

u8 RTC_Test_RAM(void)
{
	u8 wr=0,rd;
	char str[48];

	for (wr = 0; wr < 0x80;wr++)
	{
		RTC_WriteSRAM(0,wr);
		rd = RTC_ReadSRAM(0);
		if (wr!=rd)
		{
			sprintf(str,"\tRTC RAM Fail - WR 0x%02X, RD 0x%02X\n\r",wr,rd);
			Cli_print(str);
			return(0);
		}
	}
	Cli_print("\tRTC RAM ok.\n\r");
	return(1);
}

// It is assumed that the XTAL has been enabled
u8 RTC_Test_XTAL(void)
{
	int timeout = 1000;

	do
	{
		if (RTC_ReadReg(0x03) & 0x20) break;
		RTC_delay();
		timeout--;

	} while(timeout);

	if(timeout>0)
		Cli_print("\tRTC xtal ok.\n\r");
	else
		Cli_print("\tRTC xtal FAIL.\n\r");

	return(timeout ? 1:0);
}

u8 RTC_Test_MFP(void)
{
	u8 pass = 1;

	RTC_MFP_Set(1);

	if (RTC_MFP_Get() == 0)
	{
		pass = 0;
	}
	else
	{
		RTC_MFP_Set(0);
		if (RTC_MFP_Get() == 1) pass = 0;
	}

	if(pass)
		Cli_print("\tRTC MFP ok.\n\r");
	else
		Cli_print("\tRTC MFP FAIL.\n\r");
	return(pass);
}


u8 RTC_MFP_Get(void)
{
	return GpioController_Read(MCP79400_DEV1_GPIO_MFP);
}

void RTC_MFP_Set(u8 val)
{
	u8 R07 = RTC_ReadReg(0x07);

	if (val) R07 |= 0x80;
	else R07 &= ~0x80;

	RTC_WriteReg(0x07,R07);

}

bool RTC_SelfTest()
{
	bool pass = true;

	if(!RTC_Test_XTAL())
		pass = false;
	if(!RTC_Test_RAM())
		pass = false;
	if(!RTC_Test_MFP())
		pass = false;
	return pass;
}

void MCP79400_init()
{
#ifdef MCP79400_CLI
	S_CLI cli;

	cli.cli = (PFV_S)rtc_cli;
	cli.command = rtc_command;
	cli_install(&cli);

#endif

	GpioController_SetDir(MCP79400_DEV1_GPIO_MFP, 0);

	I2cController_AddDevice(MCP79400_DEV1_I2C_BUS, MCP79400_DEV1_I2C_ADDR, MCP79400_DEV1_I2C_BUS_DEVICE_NUM, 0, 0);

	// Start the oscillator
	RTC_WriteReg(0x00,0x80);		// Enable the Oscillator
	RTC_WriteReg(0x07,0x00);		// MFP is a GPIO output, set as 0
	RTC_WriteReg(0x03,0x08);		// Enable the battery


}





