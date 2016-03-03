#include "LEDs_config.h"
#include "LEDs.h"
#include "gpio/GpioController.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "uart.h"

#if defined(LEDS_CLI_TEST)
#include "cli.h"

static char LEDs_test_cmd[] = "leds";
static void LEDs_test(char *parms);

static void LEDs_test(char *parms)
{
	uint8_t cmd;

	sscanf(parms,"%1c",&cmd);

	switch(cmd)
	{
	case 't':
		LEDs_test_on();
		break;

	case 'f':
		LEDs_test_off();
		break;

	default:
		Cli_print("\n\rleds t - Turns all LEDs on");
		Cli_print("\n\rleds f - Turns all LEDs off");
		Cli_print("\n\rleds ? - Displays this help message");
		break;
	}
}
#endif

void LEDs_On(uint16_t index)
{
	if(LEDs_ActiveHigh[index])
		GpioController_SetVal(LEDs_Array[index], 1);
	else
		GpioController_SetVal(LEDs_Array[index], 0);
}

void LEDs_Off(uint16_t index)
{
	if(LEDs_ActiveHigh[index])
		GpioController_SetVal(LEDs_Array[index], 0);
	else
		GpioController_SetVal(LEDs_Array[index], 1);
}

bool LEDs_test_on()
{
	int i;
	Cli_print("\tTurning all LEDs on (D1-4, D6-13, D40-41).\n\r");
	for(i=0; i<LEDS_TOTAL_NUMBER+1; i++)
		LEDs_On(i);
	return true;
}

bool LEDs_test_off()
{
	int i;
	Cli_print("\tTurning all LEDs off (D1-4, D6-13, D40-41).\n\r");
	for(i=0; i<LEDS_TOTAL_NUMBER+1; i++)
		LEDs_Off(i);
	return true;
}

void LEDs_setup()
{
	// Todo
}

void LEDs_init()
{
	int i;

#if defined(LEDS_CLI_TEST)
    S_CLI cli;

    cli.cli = (PFV_S)LEDs_test;
    cli.command = LEDs_test_cmd;
    cli_install(&cli);
#endif
    for(i=0; i<LEDS_TOTAL_NUMBER+1; i++)
    {
    	GpioController_SetDir(LEDs_Array[i], 1);
    }

    for(i=0; i<LEDS_TOTAL_NUMBER+1; i++)
    {
    	GpioController_SetOutputEn(LEDs_Array[i], 1);
    }
}


