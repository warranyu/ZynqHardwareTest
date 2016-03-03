#include "I2cDriver.h"

void I2cDriver_Init(I2cDriver self)
{
    if (self)
        self->vtable->Init(self);
}

bool I2cDriver_IsBusy(I2cDriver self)
{
    if (self)
        return self->vtable->IsBusy(self);
    else
    	return false;
}

bool I2cDriver_AddDevice(I2cDriver self, uint8_t i2c_address, uint8_t device_num, uint32_t clock_rate, uint32_t timeout)
{
	if(device_num > I2C_MAX_DEVICES)
		return false;

	if (self)
		return self->vtable->AddDevice(self, i2c_address, device_num, clock_rate, timeout);
	else
		return false;
}

void I2cDriver_Write(I2cDriver self, uint8_t device_num, uint8_t * data, uint16_t len, uint8_t stop)
{
    if (self)
        self->vtable->Write(self, device_num, data, len, stop);
}

void I2cDriver_Read(I2cDriver self, uint8_t device_num, uint8_t * data, uint16_t len, uint8_t stop)
{
    if (self)
        self->vtable->Read(self, device_num, data, len, stop);
}

void I2cDriver_Destroy(I2cDriver self)
{
    if (self)
        self->vtable->Destroy(self);
}

const char * I2cDriver_GetType(I2cDriver driver)
{
    return driver->type;
}

int I2cDriver_GetID(I2cDriver driver)
{
    return driver->bus_num;
}
