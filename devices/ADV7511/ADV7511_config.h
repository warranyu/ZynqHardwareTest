/*
 * File:   ADV7511_config.h
 * Author: wwalton
 *
 * Created on April 21, 2015, 11:02 AM
 */

#ifndef ADV7511_CONFIG_H
#define	ADV7511_CONFIG_H


/* Which instances would you like to enable? */
#define ADV7511_DEV1
#define ADV7511_DEV2
#define ADV7511_DEV3
#define ADV7511_DEV4

/* Would you like a CLI test command? */
//#define ADV7511_CLI_TEST

/* Define the bus, address, and clock speed */
#ifdef ADV7511_DEV1
#define ADV7511_DEV1_I2C_BUS 0
#define ADV7511_DEV1_I2C_BUS_DEVICE_NUM	0
#define ADV7511_DEV1_I2C_ADDR 0x7A
#define ADV7511_DEV1_I2C_CLK 400000
#define ADV7511_DEV1_I2C_TIMEOUT 10000
#endif

#ifdef ADV7511_DEV2
#define ADV7511_DEV2_I2C_BUS 2
#define ADV7511_DEV2_I2C_BUS_DEVICE_NUM	0
#define ADV7511_DEV2_I2C_ADDR 0x72
#define ADV7511_DEV2_I2C_CLK 400000
#define ADV7511_DEV2_I2C_TIMEOUT 10000
#endif

#ifdef ADV7511_DEV3
#define ADV7511_DEV3_I2C_BUS 2
#define ADV7511_DEV3_I2C_BUS_DEVICE_NUM	1
#define ADV7511_DEV3_I2C_ADDR 0x7A
#define ADV7511_DEV3_I2C_CLK 400000
#define ADV7511_DEV3_I2C_TIMEOUT 10000
#endif

#ifdef ADV7511_DEV4
#define ADV7511_DEV4_I2C_BUS 3
#define ADV7511_DEV4_I2C_BUS_DEVICE_NUM	0
#define ADV7511_DEV4_I2C_ADDR 0x72
#define ADV7511_DEV4_I2C_CLK 400000
#define ADV7511_DEV4_I2C_TIMEOUT 10000
#endif

#endif	/* ADV7511_CONFIG_H */

