#include "ZynqPSGpioDriver.h"
#include "GpioDriverPrivate.h"
#include <stdlib.h>

typedef struct ZynqPSGpioDriverStruct
{
    GpioDriverStruct base;
    uint32_t address;
} ZynqPSGpioDriverStruct;

static void init(GpioDriver super)
{
	ZynqPSGpioDriver self = (ZynqPSGpioDriver) super;
	// Init whatever clocks, etc. that needs to be init'd
}

static void setOutputEn(GpioDriver super, uint16_t gpio_pin, uint16_t gpio_en)
{
	uint32_t OpEnableReg = 0;
	ZynqPSGpioDriver self = (ZynqPSGpioDriver) super;

	OpEnableReg = *(volatile uint32_t *) (self->address + (self->base.bank * XGPIOPS_REG_MASK_OFFSET) + XGPIOPS_OUTEN_OFFSET);

	if (gpio_en) { /*  Enable Output Enable */
		OpEnableReg |= (1 << gpio_pin);
	} else { /* Disable Output Enable */
		OpEnableReg &= ~ (1 << gpio_pin);
	}

	*(volatile uint32_t *) (self->address + (self->base.bank * XGPIOPS_REG_MASK_OFFSET) + XGPIOPS_OUTEN_OFFSET) = OpEnableReg;
}


static void setDir(GpioDriver super, uint16_t gpio_pin, uint16_t gpio_dir)
{
	uint32_t DirModeReg = 0;
	ZynqPSGpioDriver self = (ZynqPSGpioDriver) super;

	DirModeReg = *(volatile uint32_t *) (self->address + (self->base.bank * XGPIOPS_REG_MASK_OFFSET) + XGPIOPS_DIRM_OFFSET);

	if (gpio_dir) { /*  Output Direction */
		DirModeReg |= (1 << gpio_pin);
	} else { /* Input Direction */
		DirModeReg &= ~ (1 << gpio_pin);
	}

	*(volatile uint32_t *) (self->address + (self->base.bank * XGPIOPS_REG_MASK_OFFSET) + XGPIOPS_DIRM_OFFSET) = DirModeReg;
}

static void setVal(GpioDriver super, uint16_t gpio_pin, uint16_t gpio_val)
{
	ZynqPSGpioDriver self = (ZynqPSGpioDriver) super;
	uint32_t PinNumber = gpio_pin;
	uint32_t Value;
	uint32_t RegOffset;

	if (PinNumber > 15) {
		/*
		 * There are only 16 data bits in bit maskable register.
		 */
		PinNumber -= 16;
		RegOffset = XGPIOPS_DATA_MSW_OFFSET;
	} else {
		RegOffset = XGPIOPS_DATA_LSW_OFFSET;
	}

	/*
	 * Get the 32 bit value to be written to the Mask/Data register where
	 * the upper 16 bits is the mask and lower 16 bits is the data.
	 */
	gpio_val &= 0x01;
	Value = ~(1 << (PinNumber + 16)) & ((gpio_val << PinNumber) | 0xFFFF0000);
	*(volatile uint32_t *) (self->address + (self->base.bank * XGPIOPS_REG_MASK_OFFSET) + RegOffset) = Value;
}

static uint16_t read(GpioDriver super, uint16_t gpio_pin)
{
	ZynqPSGpioDriver self = (ZynqPSGpioDriver) super;
	uint32_t PinNumber = gpio_pin;

	return ((*(volatile uint32_t *) (self->address + (self->base.bank * XGPIOPS_DATA_BANK_OFFSET) + XGPIOPS_DATA_RO_OFFSET) >> PinNumber) & 1);
}

static void destroy(GpioDriver super)
{
	ZynqPSGpioDriver self = (ZynqPSGpioDriver) super;
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

GpioDriver ZynqPSGpioDriver_Create(uint16_t bank, uint32_t address)
{
	ZynqPSGpioDriver self = calloc(1, sizeof(ZynqPSGpioDriverStruct));
    self->base.vtable = &interface;
    self->base.type = "ZynqPS";
    self->base.bank = bank;
    self->address = address;
    return (GpioDriver)self;
}
