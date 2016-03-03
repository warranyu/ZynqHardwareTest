#include "I2cController.h"
#include <stdlib.h>
#include "I2cDriver.h"
#include <stdbool.h>
#include <stdint.h>

static I2cDriver i2cDrivers[MAX_I2C_BUSES] = {NULL};

void I2cController_Create(void)
{
	memset(i2cDrivers, 0, sizeof(i2cDrivers));
}

void I2cController_Destroy(void)
{
	int i;
	for(i=0; i<MAX_I2C_BUSES; i++)
	{
		I2cDriver driver = i2cDrivers[i];
		I2cDriver_Destroy(driver);
		i2cDrivers[i] = NULL;
	}
}

static bool isIdInBounds(uint16_t bus_num)
{
	return (bus_num < 0 || bus_num >= MAX_I2C_BUSES);
}

bool I2cController_Add(uint16_t bus_num, I2cDriver i2cDriver)
{
	if(isIdInBounds(bus_num))
		return false;

	if(i2cDriver == NULL)
		return false;

	I2cDriver_Destroy(i2cDrivers[bus_num]);

	i2cDrivers[bus_num] = i2cDriver;
	return true;
}

bool I2cController_Remove(uint16_t bus_num)
{
	if(isIdInBounds(bus_num))
		return false;

	if(i2cDrivers[bus_num] == NULL)
		return false;

	I2cDriver_Destroy(i2cDrivers[bus_num]);

	i2cDrivers[bus_num] = NULL;
	return true;
}

void I2cController_Init(uint16_t bus_num)
{
	if(isIdInBounds(bus_num))
		return;

	if(i2cDrivers[bus_num] == NULL)
		return;

	I2cDriver_Init(i2cDrivers[bus_num]);
}

bool I2cController_AddDevice(uint16_t bus_num, uint8_t i2c_address, uint8_t device_num, uint32_t clock_rate, uint32_t timeout)
{
	if(isIdInBounds(bus_num))
		return false;

	if(i2cDrivers[bus_num] == NULL)
		return false;

	return I2cDriver_AddDevice(i2cDrivers[bus_num], i2c_address, device_num, clock_rate, timeout);
}

bool I2cController_IsBusy(uint16_t bus_num)
{
	if(isIdInBounds(bus_num))
		return true;

	if(i2cDrivers[bus_num] == NULL)
		return true;

	return I2cDriver_IsBusy(i2cDrivers[bus_num]);
}

void I2cController_Write(uint16_t bus_num, uint8_t device_num, uint8_t * data, uint16_t len, uint8_t stop)
{
	if(isIdInBounds(bus_num))
		return;

	if(i2cDrivers[bus_num] == NULL)
		return;

	I2cDriver_Write(i2cDrivers[bus_num], device_num, data, len, stop);
}

void I2cController_Read(uint16_t bus_num, uint8_t device_num, uint8_t * data, uint16_t len, uint8_t stop)
{
	if(isIdInBounds(bus_num))
		return;

	if(i2cDrivers[bus_num] == NULL)
		return;

	I2cDriver_Read(i2cDrivers[bus_num], device_num, data, len, stop);
}
