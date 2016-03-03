#ifndef SpiController_H
#define SpiController_H

#include "SpiDriver.h"
#include <stdint.h>
#include <stdbool.h>

enum {MAX_SPI_BUSES = 10};

void SpiController_Create(void);
void SpiController_Destroy(void);
void SpiController_Init(uint16_t bus_num);
bool SpiController_AddDevice(uint16_t bus_num, uint8_t chipsel, uint8_t device_num, uint32_t speed, uint32_t timeout);
void SpiController_AssertCS(uint16_t bus_num, uint8_t device_num);
void SpiController_NegateCS(uint16_t bus_num);
void SpiController_Write(uint16_t bus_num, uint8_t device_num, uint8_t * data, uint16_t len);
void SpiController_Read(uint16_t bus_num, uint8_t device_num, uint8_t * data, uint16_t len);
bool SpiController_Add(uint16_t bus_num, SpiDriver spiDriver);
bool SpiController_Remove(uint16_t bus_num);

#endif  /* SpiController_H */

