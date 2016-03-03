#include "ZynqPLGpioDriver.h"
#include "GpioDriverPrivate.h"
#include <stdlib.h>

typedef struct ZynqPLGpioDriverStruct
{
    GpioDriverStruct base;
    uint32_t address;
    uint32_t shadow;
} ZynqPLGpioDriverStruct;

static void init(GpioDriver super)
{
	ZynqPLGpioDriver self = (ZynqPLGpioDriver) super;
	// Init whatever clocks, etc. that needs to be init'd
	self->shadow = 0;
	*(volatile uint32_t *) (self->address + XGPIO_DATA_OFFSET) = 0;
}

static void setOutputEn(GpioDriver super, uint16_t gpio_pin, uint16_t gpio_en)
{
	// AXI_GPIO has no output enable
	return;
}


static void setDir(GpioDriver super, uint16_t gpio_pin, uint16_t gpio_dir)
{
	uint32_t DirModeReg = 0;
	ZynqPLGpioDriver self = (ZynqPLGpioDriver) super;

	DirModeReg = *(volatile uint32_t *) (self->address + XGPIO_TRI_OFFSET);

	if (gpio_dir) { /*  Output Direction */
		DirModeReg |= (1 << gpio_pin);
	} else { /* Input Direction */
		DirModeReg &= ~ (1 << gpio_pin);
	}

	*(volatile uint32_t *) (self->address + XGPIO_TRI_OFFSET) = DirModeReg;
}

static void setVal(GpioDriver super, uint16_t gpio_pin, uint16_t gpio_val)
{
	ZynqPLGpioDriver self = (ZynqPLGpioDriver) super;
	uint32_t RegValue;

	RegValue = self->shadow;

	if(gpio_val)
		RegValue |= (1<<gpio_pin);
	else
		RegValue &= ~(1<<gpio_pin);

	self->shadow = RegValue;
	*(volatile uint32_t *) (self->address + XGPIO_DATA_OFFSET) = RegValue;
}

static uint16_t read(GpioDriver super, uint16_t gpio_pin)
{
	ZynqPLGpioDriver self = (ZynqPLGpioDriver) super;
	uint32_t RegValue;
	uint16_t out = 0;

	RegValue = *(volatile uint32_t *) (self->address + XGPIO_DATA_OFFSET);

	if(RegValue & (1<<gpio_pin))
		out = 1;

	return out;
}

static void destroy(GpioDriver super)
{
	ZynqPLGpioDriver self = (ZynqPLGpioDriver) super;
    free(self);
}

static GpioDriverInterfaceStruct interface =
{
	init,
	setOutputEn,
	setDir,
	setVal,
	read,
	destroy
};

GpioDriver ZynqPLGpioDriver_Create(uint16_t bank, uint32_t address)
{
	ZynqPLGpioDriver self = calloc(1, sizeof(ZynqPLGpioDriverStruct));
    self->base.vtable = &interface;
    self->base.type = "ZynqPL";
    self->base.bank = bank;
    self->address = address;
    return (GpioDriver)self;
}
