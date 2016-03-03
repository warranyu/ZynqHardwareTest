#ifndef I2cDriverPrivate_H
#define I2cDriverPrivate_H

#define I2C_MAX_DEVICES 8

typedef struct
{
    uint8_t     address;		/**< The device's 7bit address*/
    uint32_t    clock_rate;		/**< The data rate for this device*/
    uint32_t	timeout;
}i2c_device_t;

typedef struct I2cDriverInterfaceStruct * I2cDriverInterface;

typedef struct I2cDriverStruct
{
    I2cDriverInterface vtable;					// Pointer to vector table of I2c driver interface functions
    const char * type;							// String containing the name of the GPIO driver
    uint16_t bus_num;							// Bus number for this I2C bus.
    i2c_device_t *device[I2C_MAX_DEVICES];		// Array of pointers to multiple I2C device information structs. Supports up to 8 devices per bus.
} I2cDriverStruct;

typedef struct I2cDriverInterfaceStruct
{
    void (*Init)(I2cDriver);
    bool (*IsBusy)(I2cDriver);
    bool (*AddDevice)(I2cDriver, uint8_t i2c_address, uint8_t device_num, uint32_t clock_rate, uint32_t timeout);
    void (*Write)(I2cDriver, uint8_t device_num, uint8_t * data, uint16_t len, uint8_t stop);
    void (*Read)(I2cDriver, uint8_t device_num, uint8_t * data, uint16_t len, uint8_t stop);
    void (*Destroy)(I2cDriver);
} I2cDriverInterfaceStruct;

#endif  /* I2cDriverPrivate_H */
