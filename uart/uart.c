/*
 * i2C.c

 *
 *  Created on: Nov 10, 2013
 *      Author: jdecesare
 */
#include <stdio.h>
#include "uart.h"
#include "cli.h"
#include "ctypes.h"
#include "xuartlite_l.h"


static char uart_command[] = "uart";
static void uart_cli(char *parms);



static RESULT uart_Loopback(void);

// Debug UART Routines
void Cli_print(char *s)
{
	while(*s != 0)
			XUartPs_SendByte(STDOUT_BASEADDRESS,*s++);
}

void Cli_putc(char c)
{
	XUartPs_SendByte(STDOUT_BASEADDRESS,c);
}

char Cli_ischar(void)
{
	return(XUartPs_IsReceiveData(STDOUT_BASEADDRESS));
}

char Cli_getc(void)
{
	return(XUartPs_RecvByte(STDOUT_BASEADDRESS));
}

// PL UART Routines

// PL0 Feeder Interface
// PL1 Pass through Interface
void pl0_print(char *s)
{
	while(*s != 0)
			XUartLite_WriteReg(XPAR_AXI_UARTLITE_0_BASEADDR, XUL_TX_FIFO_OFFSET, *s++);
}

void pl0_putc(char c)
{
	XUartLite_WriteReg(XPAR_AXI_UARTLITE_0_BASEADDR, XUL_TX_FIFO_OFFSET, c);
}

char pl0_ischar(void)
{
	return(!XUartLite_IsReceiveEmpty(XPAR_AXI_UARTLITE_0_BASEADDR));
}

char pl0_getc(void)
{
	return XUartLite_ReadReg(XPAR_AXI_UARTLITE_0_BASEADDR, XUL_RX_FIFO_OFFSET);
}

void pl1_print(char *s)
{
	while(*s != 0)
			XUartLite_WriteReg(XPAR_AXI_UARTLITE_1_BASEADDR, XUL_TX_FIFO_OFFSET, *s++);
}

void pl1_putc(char c)
{
	XUartLite_WriteReg(XPAR_AXI_UARTLITE_1_BASEADDR, XUL_TX_FIFO_OFFSET, c);
}

char pl1_ischar(void)
{
	return(!XUartLite_IsReceiveEmpty(XPAR_AXI_UARTLITE_1_BASEADDR));
}

char pl1_getc(void)
{
	return XUartLite_ReadReg(XPAR_AXI_UARTLITE_1_BASEADDR, XUL_RX_FIFO_OFFSET);
}



void UART_Init(void)
{

	S_CLI cli;

	cli.cli = (PFV_S)uart_cli;
	cli.command = uart_command;
	cli_install(&cli);

}

static void uart_cli(char *parms)
{
	u8 cmd;


	sscanf(parms,"%1c",&cmd);

	switch(cmd)
	{

		case 'p':
		pl0_print("\n\rTesting PL0 UART");
		break;

		default:
		Cli_print("\n\rUART ? - Displays this help menu");
		Cli_print("\n\rUART P - Prints a string out the PS0 Port");
		break;
	}


}

