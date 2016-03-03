#include <stdint.h>
#include <stdbool.h>

#define LEDS_CLI_TEST

#define LEDS_TOTAL_NUMBER	14

#define PS_LED0				9
#define PS_LED1				10
#define PS_LED2				11
#define PS_LED3				12
#define LED0				129			// AXI_GPIO_0 [1]
#define LED1				130			// AXI_GPIO_0 [2]
#define LED2				131			// AXI_GPIO_0 [3]
#define LED3				132			// AXI_GPIO_0 [4]
#define LED4				133			// AXI_GPIO_0 [5]
#define LED5				134			// AXI_GPIO_0 [6]
#define LED6				135			// AXI_GPIO_0 [7]
#define LED7				136			// AXI_GPIO_0 [8]
#define ZYNQ_STBY_LED		137			// AXI_GPIO_0 [9]
#define ZYNQ_ON_LED			138			// AXI_GPIO_0 [10]

uint32_t LEDs_Array[LEDS_TOTAL_NUMBER] = {
		PS_LED0,
		PS_LED1,
		PS_LED2,
		PS_LED3,
		LED0,
		LED1,
		LED2,
		LED3,
		LED4,
		LED5,
		LED6,
		LED7,
		ZYNQ_STBY_LED,
		ZYNQ_ON_LED
};

bool LEDs_ActiveHigh[LEDS_TOTAL_NUMBER] =
{
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		false,
		true,
		true
};
