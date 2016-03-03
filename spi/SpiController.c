#include "SpiController.h"
#include <stdlib.h>
#include "SpiDriver.h"
#include <stdbool.h>
#include <stdint.h>

static SpiDriver SpiDrivers[MAX_SPI_BUSES] = {NULL};

void SpiController_Create(void)
{
	memset(SpiDrivers, 0, sizeof(SpiDrivers));
}

void SpiController_Destroy(void)
{
	int i;
	for(i=0; i<MAX_SPI_BUSES; i++)
	{
		SpiDriver driver = SpiDrivers[i];
		SpiDriver_Destroy(driver);
		SpiDrivers[i] = NULL;
	}
}

static bool isIdInBounds(uint16_t bus_num)
{
	return (bus_num < 0 || bus_num >= MAX_SPI_BUSES);
}

bool SpiController_Add(uint16_t bus_num, SpiDriver SpiDriver)
{
	if(isIdInBounds(bus_num))
		return false;

	if(SpiDriver == NULL)
		return false;

	SpiDriver_Destroy(SpiDrivers[bus_num]);

	SpiDrivers[bus_num] = SpiDriver;
	return true;
}

bool SpiController_Remove(uint16_t bus_num)
{
	if(isIdInBounds(bus_num))
		return false;

	if(SpiDrivers[bus_num] == NULL)
		return false;

	SpiDriver_Destroy(SpiDrivers[bus_num]);

	SpiDrivers[bus_num] = NULL;
	return true;
}

void SpiController_Init(uint16_t bus_num)
{
	if(isIdInBounds(bus_num))
		return;

	if(SpiDrivers[bus_num] == NULL)
		return;

	SpiDriver_Init(SpiDrivers[bus_num]);
}

bool SpiController_AddDevice(uint16_t bus_num, uint8_t chipsel, uint8_t device_num, uint32_t speed, uint32_t timeout)
{
	if(isIdInBounds(bus_num))
		return false;

	if(SpiDrivers[bus_num] == NULL)
		return false;

	return SpiDriver_AddDevice(SpiDrivers[bus_num], chipsel, device_num, speed, timeout);
}

void SpiController_AssertCS(uint16_t bus_num, uint8_t device_num)
{
	if(isIdInBounds(bus_num))
		return;

	if(SpiDrivers[bus_num] == NULL)
		return;

	SpiDriver_AssertCS(SpiDrivers[bus_num], device_num);
}

void SpiController_NegateCS(uint16_t bus_num)
{
	if(isIdInBounds(bus_num))
		return;

	if(SpiDrivers[bus_num] == NULL)
		return;

	SpiDriver_NegateCS(SpiDrivers[bus_num]);
}

void SpiController_Write(uint16_t bus_num, uint8_t device_num, uint8_t * data, uint16_t len)
{
	if(isIdInBounds(bus_num))
		return;

	if(SpiDrivers[bus_num] == NULL)
		return;

	SpiDriver_Write(SpiDrivers[bus_num], device_num, data, len);
}

void SpiController_Read(uint16_t bus_num, uint8_t device_num, uint8_t * data, uint16_t len)
{
	if(isIdInBounds(bus_num))
		return;

	if(SpiDrivers[bus_num] == NULL)
		return;

	SpiDriver_Read(SpiDrivers[bus_num], device_num, data, len);
}
