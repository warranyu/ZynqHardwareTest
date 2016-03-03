#include "GpioController.h"
#include <stdlib.h>
#include "GpioDriver.h"
#include <stdbool.h>
#include <stdint.h>

static GpioDriver gpioDrivers[MAX_GPIO_BANKS] = {NULL};

void GpioController_Create(void)
{
	memset(gpioDrivers, 0, sizeof(gpioDrivers));
}

void GpioController_Destroy(void)
{
	int i;
	for(i=0; i<MAX_GPIO_BANKS; i++)
	{
		GpioDriver driver = gpioDrivers[i];
		GpioDriver_Destroy(driver);
		gpioDrivers[i] = NULL;
	}
}

static uint16_t get_bank_num(uint16_t gpio_num)
{
	return gpio_num/32;
}

static uint16_t get_pin_num(uint16_t gpio_num)
{
	return gpio_num%32;
}


static bool isIdInBounds(uint16_t gpio_bank)
{
	return (gpio_bank < 0 || gpio_bank >= MAX_GPIO_BANKS);
}

bool GpioController_Add(uint16_t gpio_bank, GpioDriver gpioDriver)
{
	if(isIdInBounds(gpio_bank))
		return false;

	if(gpioDriver == NULL)
		return false;

	GpioDriver_Destroy(gpioDrivers[gpio_bank]);

	gpioDrivers[gpio_bank] = gpioDriver;
	return true;
}

bool GpioController_Remove(uint16_t gpio_bank)
{
	if(isIdInBounds(gpio_bank))
		return false;

	if(gpioDrivers[gpio_bank] == NULL)
		return false;

	GpioDriver_Destroy(gpioDrivers[gpio_bank]);

	gpioDrivers[gpio_bank] = NULL;
	return true;
}

void GpioController_Init(uint16_t gpio_bank)
{
	GpioDriver_Init(gpioDrivers[gpio_bank]);
}

void GpioController_SetOutputEn(uint16_t gpio_num, uint16_t gpio_en)
{
	uint16_t gpio_bank = get_bank_num(gpio_num);
	uint16_t gpio_pin = get_pin_num(gpio_num);
	GpioDriver_SetOutputEn(gpioDrivers[gpio_bank], gpio_pin, gpio_en);
}

void GpioController_SetDir(uint16_t gpio_num, uint16_t gpio_dir)
{
	uint16_t gpio_bank = get_bank_num(gpio_num);
	uint16_t gpio_pin = get_pin_num(gpio_num);
	GpioDriver_SetDir(gpioDrivers[gpio_bank], gpio_pin, gpio_dir);
}

void GpioController_SetVal(uint16_t gpio_num, uint16_t gpio_val)
{
	uint16_t gpio_bank = get_bank_num(gpio_num);
	uint16_t gpio_pin = get_pin_num(gpio_num);
	GpioDriver_SetVal(gpioDrivers[gpio_bank], gpio_pin, gpio_val);
}

uint16_t GpioController_Read(uint16_t gpio_num)
{
	uint16_t gpio_bank = get_bank_num(gpio_num);
	uint16_t gpio_pin = get_pin_num(gpio_num);
	return GpioDriver_Read(gpioDrivers[gpio_bank], gpio_pin);
}


