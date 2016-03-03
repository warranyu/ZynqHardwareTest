#include "GpioDriver.h"

void GpioDriver_Init(GpioDriver self)
{
    if (self)
        self->vtable->Init(self);
}

void GpioDriver_SetOutputEn(GpioDriver self, uint16_t gpio_pin, uint16_t gpio_en)
{
    if (self)
        self->vtable->SetOutputEn(self, gpio_pin, gpio_en);
}

void GpioDriver_SetDir(GpioDriver self, uint16_t gpio_pin, uint16_t gpio_dir)
{
    if (self)
        self->vtable->SetDir(self, gpio_pin, gpio_dir);
}

void GpioDriver_SetVal(GpioDriver self, uint16_t gpio_pin, uint16_t gpio_val)
{
    if (self)
        self->vtable->SetVal(self, gpio_pin, gpio_val);
}

uint16_t GpioDriver_Read(GpioDriver self, uint16_t gpio_pin)
{
    if (self)
        return self->vtable->Read(self, gpio_pin);
    else
    	return 0;
}

void GpioDriver_Destroy(GpioDriver self)
{
    if (self)
        self->vtable->Destroy(self);
}

const char * GpioDriver_GetType(GpioDriver driver)
{
    return driver->type;
}

int GpioDriver_GetBank(GpioDriver driver)
{
    return driver->bank;
}
