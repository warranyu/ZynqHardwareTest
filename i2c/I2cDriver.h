#ifndef I2cDriver_H
#define I2cDriver_H

#include <stdint.h>
#include <stdbool.h>

typedef struct I2cDriverStruct  * I2cDriver;

void I2cDriver_Init(I2cDriver);
bool I2cDriver_IsBusy(I2cDriver);
bool I2cDriver_AddDevice(I2cDriver, uint8_t i2c_address, uint8_t device_num, uint32_t clock_rate, uint32_t timeout);
void I2cDriver_Write(I2cDriver, uint8_t device_num, uint8_t * data, uint16_t len, uint8_t stop);
void I2cDriver_Read(I2cDriver, uint8_t device_num, uint8_t * data, uint16_t len, uint8_t stop);
void I2cDriver_Destroy(I2cDriver);
const char * I2cDriver_GetType(I2cDriver driver);
int I2cDriver_GetID(I2cDriver);


#include "I2cDriverPrivate.h"

#endif  /* I2cDriver_H */
