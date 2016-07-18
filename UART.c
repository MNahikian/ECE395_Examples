/*----------------------------------------------------------------------------
 * Name:    Serial.c
 * Purpose: Low level serial routines
 * Note(s):
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2010 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/

#include "LPC11xx.h"
#include "UART.h"

/*----------------------------------------------------------------------------
  Initialize UART pins, Baudrate 115200
 *----------------------------------------------------------------------------*/
void UART_Init (void) {
   
  LPC_SYSCON->SYSAHBCLKCTRL |= (1UL <<  6);  //enable clocks to GPIO block (sec 3.5.14)
  LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 16);  //enable clocks to IOCON block (sec 3.5.14)

  LPC_IOCON->PIO1_6 = (1UL <<  0);           //select pin function RXD (sec 7.4.40)
  LPC_IOCON->PIO1_7 = (1UL <<  0);           //select pin funstion TXD (sec 7.4.41)

  /* configure UART0 */
  LPC_SYSCON->SYSAHBCLKCTRL |=  (1UL << 12); //enable clock to UART (sec 3.5.14)
  LPC_SYSCON->UARTCLKDIV     =  (4UL <<  0); //enable UART clock =  CCLK / 4 (sec 3.5.16)

  LPC_UART->LCR = 0x83;                      /*set 8 bit character length,
	                                            *one stop bit,
	                                            *parity disabled,
	                                            *enable access to Divisor Latches,
																					    *(sec 13.5.7)*/
	
  LPC_UART->DLL = 4;                         //set 115200 Baud Rate @ 12.0 MHZ PCLK (sec 13.5.15 & 13.5.3)
  LPC_UART->FDR = 0x85;                      //set FR 1.627, DIVADDVAL 5, MULVAL 8  (sec 13.5.15)
  LPC_UART->DLM = 0;                         //set High divisor latch = 0 (sec 13.5.15 & 13.5.3)
  LPC_UART->LCR = 0x03;                      //disable access to Divisor Latches (sec 13.5.7)
}


/*----------------------------------------------------------------------------
  Write character to Serial Port
	Overrides fputc() via Retarget.c
 *----------------------------------------------------------------------------*/
int sendchar (int c) {
  while (!(LPC_UART->LSR & 0x20)); //wait until the THR is free (sec 13.5.9)
  LPC_UART->THR = c;               //set char to be transmitted (sec 13.5.2)

  return (c);
}


/*----------------------------------------------------------------------------
  Read character from Serial Port   (blocking read)
	Overrides fgetc() via Retarget.c
 *----------------------------------------------------------------------------*/
int getkey (void) {
  while (!(LPC_UART->LSR & 0x01)); //wait until the RBR is free (sec 13.5.9)
  return (LPC_UART->RBR);          //get new char (sec 13.5.1)
}
