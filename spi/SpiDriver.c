#include "SpiDriver.h"

void SpiDriver_Init(SpiDriver self)
{
    if (self)
        self->vtable->Init(self);
}

bool SpiDriver_AddDevice(SpiDriver self, uint8_t chipsel, uint8_t device_num, uint32_t clock_rate, uint32_t timeout)
{
	if(device_num > SPI_MAX_DEVICES)
		return false;

	if (self)
		return self->vtable->AddDevice(self, chipsel, device_num, clock_rate, timeout);
	else
		return false;
}

void SpiDriver_AssertCS(SpiDriver self, uint8_t device_num)
{
    if (self)
        self->vtable->AssertCS(self, device_num);
}

void SpiDriver_NegateCS(SpiDriver self)
{
    if (self)
        self->vtable->NegateCS(self);
}

void SpiDriver_Write(SpiDriver self, uint8_t device_num, uint8_t * data, uint16_t len)
{
    if (self)
        self->vtable->Write(self, device_num, data, len);
}

void SpiDriver_Read(SpiDriver self, uint8_t device_num, uint8_t * data, uint16_t len)
{
    if (self)
        self->vtable->Read(self, device_num, data, len);
}

void SpiDriver_Destroy(SpiDriver self)
{
    if (self)
        self->vtable->Destroy(self);
}

const char * SpiDriver_GetType(SpiDriver driver)
{
    return driver->type;
}

int SpiDriver_GetID(SpiDriver driver)
{
    return driver->bus_num;
}
