/*
 * File:   ADV7611_config.h
 * Author: wwalton
 *
 * Created on April 21, 2015, 11:02 AM
 */

#ifndef ADV7611_CONFIG_H
#define	ADV7611_CONFIG_H

/* Which instances would you like to enable? */
#define ADV7611_DEV1

/* Would you like a CLI test command? */
//#define ADV7611_CLI_TEST

/* Is there a GPIO reset? */
#define ADV7611_DEV1_GPIO_RST	141		// AXI GPIO 0 (bank4), pin 13

/* Define the bus, address, and clock speed */
#ifdef ADV7611_DEV1
#define ADV7611_DEV1_I2C_BUS 0
#define ADV7611_DEV1_I2C_BUS_DEVICE_NUM	1
#define ADV7611_DEV1_I2C_ADDR 0x98
#define ADV7611_DEV1_I2C_CLK 400000
#define ADV7611_DEV1_I2C_TIMEOUT 10000
#endif

#endif	/* ADV7611_CONFIG_H */

