#ifndef SpiDriver_H
#define SpiDriver_H

#include <stdint.h>
#include <stdbool.h>

typedef struct SpiDriverStruct  * SpiDriver;

void SpiDriver_Init(SpiDriver);
bool SpiDriver_AddDevice(SpiDriver, uint8_t chipsel, uint8_t device_num, uint32_t clock_rate, uint32_t timeout);
void SpiDriver_AssertCS(SpiDriver self, uint8_t device_num);
void SpiDriver_NegateCS(SpiDriver self);
void SpiDriver_Write(SpiDriver, uint8_t device_num, uint8_t * data, uint16_t len);
void SpiDriver_Read(SpiDriver, uint8_t device_num, uint8_t * data, uint16_t len);
void SpiDriver_Destroy(SpiDriver);
const char * SpiDriver_GetType(SpiDriver driver);
int SpiDriver_GetID(SpiDriver);


#include "SpiDriverPrivate.h"

#endif  /* SpiDriver_H */
