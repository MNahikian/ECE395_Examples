#include "SPI.h"

#define TNF 0x1
#define RNE 0x2

/*
* waitForStatus
*
*	Purpose : Waits until the status register changes to the specified value
*
* Inputs:
*			status : The status value to wait for
*
*/
void waitForStatusSPI(uint32_t status){
	while((LPC_SSP0->SR & status) != status); // (sec 14.6.4)
}

/*
* SPI_Init
*
*	Purpose : Initialize SPI Controller
*
*/
void SPI_Init() {
  
  LPC_IOCON->PIO0_2 |= (1UL << 0); //Set pin as SSEL0 (sec 7.4.6)
  LPC_IOCON->PIO0_6 |= (1UL << 1); //Set pin as SCK0 (sec 7.4.18)
  LPC_IOCON->PIO0_8 |= (1UL << 0); //Set pin as MISO0 (sec 7.4.23)
  LPC_IOCON->PIO0_9 |= (1UL << 0); //Set pin as MOSI0 (sec 7.4.24)

  LPC_IOCON->SCK_LOC |= (1UL << 1);         //Set SCK0 pin location as PIO0_6 (sec 7.4.43)
  LPC_SYSCON->PRESETCTRL |= (1UL << 0);     //SPI0 reset de-asserted (sec 3.5.2)
  LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 11); //Enable clock for SPI0 (sec 3.5.14)
  
	LPC_SYSCON->SSP0CLKDIV |= 0x0a; //Set SPI clock divider value (sec 3.5.15)
  LPC_SSP0->CPSR |= 0x02;         //Set SPI clock prescale value (sec 14.6.5)
  LPC_SSP0->CR0 |= 0xF;           //Select 16-bit data transfer (sec 14.6.1)
  LPC_SSP0->CR1 |= (1UL << 1);    //Enable SPI (sec 14.6.2)
}


// Send two bytes (16 bits) via SPI
/*
* SPI_Send
*
*	Purpose : Sends 16-bits of data over the SPI data line
*
* Inputs:
*			data : The 16-bits of data to send
*
*/
void SPI_Send(uint16_t data) {
  waitForStatusSPI(TNF);  //Wait for Transmit FIFO not full (sec 14.6.4)
	LPC_SSP0->DR = (uint32_t)((LPC_SSP0->DR & 0xFFFF0000) | data); //Transmit data (sec 14.6.3)
}

// Read two bytes (16 bits) via SPI
/*
* waitForStatus
*
*	Purpose : Read 16-bits of data from the SPI Data register
*
*/
uint16_t SPI_Read() {
	uint16_t data;
  waitForStatusSPI(RNE);  //Wait for Recive FIFO not full (sec 14.6.4)
  data = (uint16_t)(LPC_SSP0->DR & 0x0000FFFF); //Recive data (sec 14.6.3)
	return data;
}
