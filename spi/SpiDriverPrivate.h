#ifndef SpiDriverPrivate_H
#define SpiDriverPrivate_H

#define SPI_MAX_DEVICES 8

typedef struct
{
    uint8_t     chipsel;        /**< The device's chip select number*/
    uint32_t    speed;          /**< The bus speed for this device*/
    uint32_t	timeout;
}Spi_device_t;

typedef struct SpiDriverInterfaceStruct * SpiDriverInterface;

typedef struct SpiDriverStruct
{
    SpiDriverInterface vtable;					// Pointer to vector table of Spi driver interface functions
    const char * type;							// String containing the name of the GPIO driver
    uint16_t bus_num;							// Bus number for this Spi bus.
    Spi_device_t *device[SPI_MAX_DEVICES];		// Array of pointers to multiple Spi device information structs. Supports up to 8 devices per bus.
} SpiDriverStruct;

typedef struct SpiDriverInterfaceStruct
{
    void (*Init)(SpiDriver);
    bool (*AddDevice)(SpiDriver, uint8_t chipsel, uint8_t device_num, uint32_t speed, uint32_t timeout);
    void (*AssertCS)(SpiDriver, uint8_t device_num);
    void (*NegateCS)(SpiDriver);
    void (*Write)(SpiDriver, uint8_t device_num, uint8_t * data, uint16_t len);
    void (*Read)(SpiDriver, uint8_t device_num, uint8_t * data, uint16_t len);
    void (*Destroy)(SpiDriver);
} SpiDriverInterfaceStruct;

#endif  /* SpiDriverPrivate_H */
