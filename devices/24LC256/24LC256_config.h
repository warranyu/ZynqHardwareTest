/*
 * File:   24LC256_config.h
 * Author: wwalton
 *
 * Created on April 20, 2015, 2:47 PM
 */

#ifndef EEPROM_24LC256_CONFIG_H
#define	EEPROM_24LC256_CONFIG_H

/* Which instances would you like to enable? */
#define EEPROM_24LC256_DEV1
//#define EEPROM_24LC256_DEV2

/* Would you like a CLI test command? */
//#define EEPROM_24LC256_CLI_TEST

/* Is there a GPIO write protect? */
#define EEPROM_24LC256_GPIO_WP

/* Define the bus, address, and clock speed */
#ifdef EEPROM_24LC256_DEV1
#define EEPROM_24LC256_DEV1_I2C_BUS 			4
#define EEPROM_24LC256_DEV1_I2C_BUS_DEVICE_NUM	0
#define EEPROM_24LC256_DEV1_I2C_ADDR 			0xA0
#define EEPROM_24LC256_DEV1_I2C_CLK 			400000
#if defined(EEPROM_24LC256_GPIO_WP)
    #define EEPROM_24LC256_DEV1_GPIO_WP 		128          // Bank 4, pin 0
#endif
#define EEPROM_24LC256_DEV1_I2C_TIMEOUT 		10000
#endif

#ifdef EEPROM_24LC256_DEV2
#define EEPROM_24LC256_DEV2_I2C_BUS 1
#define EEPROM_24LC256_DEV2_I2C_ADDR 0xA2
#define EEPROM_24LC256_DEV2_I2C_CLK 400000
#if defined(EEPROM_24LC256_GPIO_WP)
    #define EEPROM_24LC256_DEV2_GPIO_WP 10             // RA10
#endif
#define EEPROM_24LC256_DEV1_I2C_TIMEOUT 10000
#endif

#endif	/* 24LC256_CONFIG_H */

