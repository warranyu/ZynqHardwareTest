#ifndef ZynqPLI2cDriver_H
#define ZynqPLI2cDriver_H

#include "I2cDriver.h"

typedef struct ZynqPLI2cDriverStruct * ZynqPLI2cDriver;

I2cDriver ZynqPLI2cDriver_Create(uint16_t bank, uint32_t address);

#include "xiic_l.h"

#endif  /*ZynqPLI2cDriver_H */
