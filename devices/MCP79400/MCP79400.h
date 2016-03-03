/*
 * MCP79400.h
 *
 *  Created on: Nov 10, 2013
 *      Author: jdecesare
 */
#ifndef MCP79400_H
#define MCP79400_H

#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xparameters.h"
#include "uart.h"
#include <stdbool.h>

#define MCP_79400_RAM_BASE 0x20
#define MCP_79400_RAM_SIZE 64

#define MCP_79400_REG_BASE 0x00
#define MCP_79400_REG_SIZE 0x60

#define MCP_79400_EEPROM_BASE 0xF0
#define MCP_79400_EEPROM_SIZE 8	// Only 8 bytes

void RTC_Init(void);
void RTC_WriteSRAM(u8 addr,u8 data);
u8 RTC_ReadSRAM(u8 addr);
void RTC_WriteReg(u8 addr,u8 data);
u8 RTC_ReadReg(u8 addr);
u8 RTC_Test_RAM(void);
u8 RTC_Test_XTAL(void);
u8 RTC_Test_MFP(void);
u8 RTC_MFP_Get(void);
void RTC_MFP_Set(u8 val);
bool RTC_SelfTest(void);
void MCP79400_init();

#endif // MCP79400_H


