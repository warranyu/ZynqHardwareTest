#ifndef I2cController_H
#define I2cController_H

#include "I2cDriver.h"
#include <stdint.h>
#include <stdbool.h>

enum {MAX_I2C_BUSES = 10};

void I2cController_Create(void);
void I2cController_Destroy(void);
void I2cController_Init(uint16_t bus_num);
bool I2cController_AddDevice(uint16_t bus_num, uint8_t i2c_address, uint8_t device_num, uint32_t clock_rate, uint32_t timeout);
bool I2cController_IsBusy(uint16_t bus_num);
void I2cController_Write(uint16_t bus_num, uint8_t device_num, uint8_t * data, uint16_t len, uint8_t stop);
void I2cController_Read(uint16_t bus_num, uint8_t device_num, uint8_t * data, uint16_t len, uint8_t stop);
bool I2cController_Add(uint16_t bus_num, I2cDriver i2cDriver);
bool I2cController_Remove(uint16_t bus_num);

#endif  /* I2cController_H */

