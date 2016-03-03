#ifndef ZynqPLSpiDriver_H
#define ZynqPLSpiDriver_H

#include "SpiDriver.h"

typedef struct ZynqPLSpiDriverStruct * ZynqPLSpiDriver;

SpiDriver ZynqPLSpiDriver_Create(uint16_t bus_num, uint32_t address);

#include "xspi_l.h"

#endif  /*ZynqPLSpiDriver_H */
