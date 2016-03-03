#ifndef GpioController_H
#define GpioController_H

#include "GpioDriver.h"
#include <stdint.h>
#include <stdbool.h>

enum {MAX_GPIO_BANKS = 16};

void GpioController_Create(void);
void GpioController_Destroy(void);
void GpioController_Init(uint16_t gpio_bank);
void GpioController_SetOutputEn(uint16_t gpio_num, uint16_t gpio_en);
void GpioController_SetDir(uint16_t gpio_num, uint16_t gpio_dir);
void GpioController_SetVal(uint16_t gpio_num, uint16_t gpio_val);
uint16_t GpioController_Read(uint16_t gpio_num);
bool GpioController_Add(uint16_t gpio_bank, GpioDriver gpioDriver);
bool GpioController_Remove(uint16_t gpio_bank);


#endif  /* GpioController_H */

