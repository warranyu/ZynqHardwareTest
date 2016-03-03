#include "ZynqPLI2cDriver.h"
#include "I2cDriverPrivate.h"
#include <stdlib.h>

typedef struct ZynqPLI2cDriverStruct
{
    I2cDriverStruct base;
    uint32_t address;
} ZynqPLI2cDriverStruct;

static void init(I2cDriver super)
{
	ZynqPLI2cDriver self = (ZynqPLI2cDriver) super;
	// Init whatever clocks, etc. that needs to be init'd
}

static bool isBusy(I2cDriver super)
{
	uint32_t StatusReg;
	ZynqPLI2cDriver self = (ZynqPLI2cDriver) super;
	StatusReg = *(volatile uint32_t *) (self->address + XIIC_SR_REG_OFFSET);
	if (StatusReg & XIIC_SR_BUS_BUSY_MASK) {
		return true;
	} else {
		return false;
	}
}

static bool addDevice(I2cDriver super, uint8_t i2c_address, uint8_t device_num, uint32_t clock_rate, uint32_t timeout)
{
	ZynqPLI2cDriver self = (ZynqPLI2cDriver) super;
	i2c_device_t * dev = malloc(sizeof(i2c_device_t));
	dev->address = i2c_address;
	dev->clock_rate = clock_rate;
	dev->timeout = timeout;
	self->base.device[device_num] = dev;
	return true;
}

static void write(I2cDriver super, uint8_t device_num, uint8_t * data, uint16_t len, uint8_t stop)
{
	ZynqPLI2cDriver self = (ZynqPLI2cDriver) super;

	if(self->base.device[device_num] == NULL)
		return;

	if(stop)
		XIic_Send(self->address, (self->base.device[device_num]->address >> 1), data, len, XIIC_STOP);
	else
		XIic_Send(self->address, (self->base.device[device_num]->address >> 1), data, len, XIIC_REPEATED_START);
}

static void read(I2cDriver super, uint8_t device_num, uint8_t * data, uint16_t len, uint8_t stop)
{
	ZynqPLI2cDriver self = (ZynqPLI2cDriver) super;

	if(self->base.device[device_num] == NULL)
		return;

	if(stop)
		XIic_Recv(self->address, (self->base.device[device_num]->address >> 1), data, len, XIIC_STOP);
	else
		XIic_Recv(self->address, (self->base.device[device_num]->address >> 1), data, len, XIIC_REPEATED_START);
}

static void destroy(I2cDriver super)
{
	ZynqPLI2cDriver self = (ZynqPLI2cDriver) super;
    free(self);
}

static I2cDriverInterfaceStruct interface =
{
	init,
	isBusy,
	addDevice,
	write,
	read,
	destroy
};

I2cDriver ZynqPLI2cDriver_Create(uint16_t bus_num, uint32_t address)
{
	ZynqPLI2cDriver self = calloc(1, sizeof(ZynqPLI2cDriverStruct));
    self->base.vtable = &interface;
    self->base.type = "ZynqPL";
    self->base.bus_num = bus_num;
    self->address = address;
    return (I2cDriver)self;
}
