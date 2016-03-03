#include "ZynqPLSpiDriver.h"
#include "SpiDriverPrivate.h"
#include <stdlib.h>

typedef struct ZynqPLSpiDriverStruct
{
    SpiDriverStruct base;
    uint32_t address;
} ZynqPLSpiDriverStruct;

static void assertCS(SpiDriver super, uint8_t device_num);
static void negateCS(SpiDriver super);

static void init(SpiDriver super)
{
	ZynqPLSpiDriver self = (ZynqPLSpiDriver) super;
	// Init whatever clocks, etc. that needs to be init'd

	//XSpi_WriteReg(spi0.baseAddress,XSP_SRR_OFFSET,XSP_SRR_RESET_MASK);  // Reset the SPI Instance
	XSpi_WriteReg(self->address,XSP_CR_OFFSET,0xE6);  // Master Config, CPOL = Active Low clock, Master Enabled, SS asserted by Slave Select Register
	negateCS(super); // Negate the Chip Selects
}

static bool addDevice(SpiDriver super, uint8_t chipsel, uint8_t device_num, uint32_t speed, uint32_t timeout)
{
	ZynqPLSpiDriver self = (ZynqPLSpiDriver) super;
	Spi_device_t * dev = malloc(sizeof(Spi_device_t));
	dev->chipsel = chipsel;
	dev->speed = speed;
	dev->timeout = timeout;
	self->base.device[device_num] = dev;
	return true;
}

static void assertCS(SpiDriver super, uint8_t device_num)
{
	ZynqPLSpiDriver self = (ZynqPLSpiDriver) super;
	XSpi_WriteReg(self->address,XSP_SSR_OFFSET,self->base.device[device_num]->chipsel);
}

static void negateCS(SpiDriver super)
{
	ZynqPLSpiDriver self = (ZynqPLSpiDriver) super;
	XSpi_WriteReg(self->address,XSP_SSR_OFFSET,0xFFFFFFFF);
}

static void write(SpiDriver super, uint8_t device_num, uint8_t * data, uint16_t len)
{
	ZynqPLSpiDriver self = (ZynqPLSpiDriver) super;

	if(self->base.device[device_num] == NULL)
		return;

	do
		{
			// See if there is room in the FIFO
			while (XSpi_ReadReg(self->address,XSP_SR_OFFSET) & XSP_SR_TX_FULL_MASK);  // Wait while the transmitter is full
			XSpi_WriteReg(self->address,XSP_DTR_OFFSET,*data++);
			len--;
		} while (len);

	// Wait until the FIFO is empty
	while (!(XSpi_ReadReg(self->address,XSP_SR_OFFSET) & XSP_SR_TX_EMPTY_MASK));  // Wait until the TX FIFO is empty
}

static void read(SpiDriver super, uint8_t device_num, uint8_t * data, uint16_t len)
{
	ZynqPLSpiDriver self = (ZynqPLSpiDriver) super;
	uint16_t i = 0;

	if(self->base.device[device_num] == NULL)
		return;

	write(super, device_num, data, len);
	do
	{
		data[i] = XSpi_ReadReg(self->address,XSP_DRR_OFFSET);
		i++;
	} while((!(XSpi_ReadReg(self->address,XSP_SR_OFFSET) & XSP_SR_RX_EMPTY_MASK)) && i<len);
}

static void destroy(SpiDriver super)
{
	ZynqPLSpiDriver self = (ZynqPLSpiDriver) super;
    free(self);
}

static SpiDriverInterfaceStruct interface =
{
	init,
	addDevice,
	assertCS,
	negateCS,
	write,
	read,
	destroy
};

SpiDriver ZynqPLSpiDriver_Create(uint16_t bus_num, uint32_t address)
{
	ZynqPLSpiDriver self = calloc(1, sizeof(ZynqPLSpiDriverStruct));
    self->base.vtable = &interface;
    self->base.type = "ZynqPL";
    self->base.bus_num = bus_num;
    self->address = address;
    return (SpiDriver)self;
}
