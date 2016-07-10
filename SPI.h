#ifndef SPI
#define SPI

#include "LPC11xx.h"

#define TNF 0x1

void SPI_init(void);
void SPI_send(uint16_t);

#endif
