#ifndef GpioDriver_H
#define GpioDriver_H

#include <stdint.h>

typedef struct GpioDriverStruct  * GpioDriver;

void GpioDriver_Init(GpioDriver);
void GpioDriver_SetOuputEn(GpioDriver, uint16_t gpio_pin, uint16_t gpio_en);
void GpioDriver_SetDir(GpioDriver, uint16_t gpio_pin, uint16_t gpio_dir);
void GpioDriver_SetVal(GpioDriver, uint16_t gpio_pin, uint16_t gpio_val);
uint16_t GpioDriver_Read(GpioDriver, uint16_t gpio_pin);
void GpioDriver_Destroy(GpioDriver);
const char * GpioDriver_GetType(GpioDriver driver);
int GpioDriver_GetBank(GpioDriver);


#include "GpioDriverPrivate.h"

#endif  /* GpioDriver_H */
