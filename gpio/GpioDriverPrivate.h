#ifndef GpioDriverPrivate_H
#define GpioDriverPrivate_H

typedef struct GpioDriverInterfaceStruct * GpioDriverInterface;

typedef struct GpioDriverStruct
{
    GpioDriverInterface vtable;			// Pointer to vector table of Gpio driver interface functions
    const char * type;					// String containing the name of the GPIO driver
    uint16_t bank;						// Bank number. Serves as id for referencing driver, must be unique.
} GpioDriverStruct;

typedef struct GpioDriverInterfaceStruct
{
    void (*Init)(GpioDriver);
    void (*SetOutputEn)(GpioDriver, uint16_t gpio_pin, uint16_t gpio_en);
    void (*SetDir)(GpioDriver, uint16_t gpio_pin, uint16_t gpio_dir);
    void (*SetVal)(GpioDriver, uint16_t gpio_pin, uint16_t gpio_val);
    uint16_t (*Read)(GpioDriver, uint16_t gpio_pin);
    void (*Destroy)(GpioDriver);
} GpioDriverInterfaceStruct;

#endif  /* GpioDriverPrivate_H */
