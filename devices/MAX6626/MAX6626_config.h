/*
 * File:   MAX6626_config.h
 * Author: wwalton
 *
 * Created on April 21, 2015, 11:02 AM
 */

#ifndef MAX6626_CONFIG_H
#define	MAX6626_CONFIG_H

/* Which instances would you like to enable? */
#define MAX6626_DEV1
#define MAX6626_DEV2

/* Are GPIO Overtemp Pins connected? */
#define MAX6626_GPIO_RST

/* Would you like a CLI test command? */
#define MAX6626_CLI

/* Define the bus, address, and clock speed */
#ifdef MAX6626_DEV1
#define MAX6626_DEV1_I2C_BUS 			4
#define MAX6626_DEV1_I2C_BUS_DEVICE_NUM	2
#define MAX6626_DEV1_I2C_ADDR			0x90
#define MAX6626_DEV1_I2C_CLK 			400000
#define MAX6626_DEV1_I2C_TIMEOUT 		10000
#ifdef	MAX6626_GPIO_RST
	#define MAX6626_DEV1_GPIO_RST		177		// AXI GPIO 1 (bank 5), pin 17
#endif
#endif

/* Define the bus, address, and clock speed */
#ifdef MAX6626_DEV2
#define MAX6626_DEV2_I2C_BUS 			4
#define MAX6626_DEV2_I2C_BUS_DEVICE_NUM	3
#define MAX6626_DEV2_I2C_ADDR 			0x92
#define MAX6626_DEV2_I2C_CLK 			400000
#define MAX6626_DEV2_I2C_TIMEOUT 		10000
#ifdef	MAX6626_GPIO_RST
	#define MAX6626_DEV2_GPIO_RST		177		// AXI GPIO 1 (bank 5), pin 17, same pin
#endif
#endif

#endif	/* MAX6626_CONFIG_H */

