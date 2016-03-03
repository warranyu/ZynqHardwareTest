/*
 * uart.h
 *
 *  Created on: Nov 10, 2013
 *      Author: jdecesare
 */
#ifndef UART_H
#define UART_H

#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xparameters.h"
#include "xuartps_hw.h"

// Debug UART
void Cli_print(char *s);
char Cli_ischar();
char Cli_getc();
void Cli_putc(char c);

// PL0 UART - Feeder
void pl0_print(char *s);
char pl0_ischar();
char pl0_getc();
void pl0_putc(char c);

// PL1 UART -- PAssThrough
void pl1_print(char *s);
char pl1_ischar();
char pl1_getc();
void pl1_putc(char c);


void UART_Init(void);


#endif // UART_H


