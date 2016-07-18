#ifndef SPI
#define SPI

#include "LPC11xx.h"

void SPI_Init(void);
void SPI_Send(uint16_t);
uint16_t SPI_Read(void);

#endif
