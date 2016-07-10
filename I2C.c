/*
* Simple I2C initialization and communication functions
*/

#include "I2C.h"
#include <stdio.h>
#include "LPC11xx.h"


//I2CSTAT Register Values (sec 15.7.2)
#define START 0x08
#define STARTR 0x10
#define SLAWACK 0x18
#define SLAWNACK 0x20
#define DATWACK 0x28
#define DATWNACK 0x30
#define LOST 0x38

#define SLARACK 0x40
#define SLARNACK 0x48
#define DATRACK 0x50
#define DATRNACK 0x58

/*
* waitForStatusI2C
*
*	Purpose : Waits until the status register changes to the specified value
*
* Inputs:
*			status : The status value to wait for
*
*/
void waitForStatusI2C(uint32_t status){
	while(LPC_I2C->STAT != status); // (sec 15.7.2)
}

/*
* I2CRead
*
*	Purpose : Read a number of bytes from the I2C Data line and store them into a buffer
*
* Inputs:
*			address  : The address of the chip to read from
*			bytes		 : The number of bytes to read
*			dataBuff : The buffer to store the read data in
*
* Documentation: (sec 15.8)
*
*/
void I2CRead(uint8_t address, uint32_t bytes, uint8_t* dataBuff){
		int i;
	
		//Clear the Interrupt and Start Registers, then send a Start Command
		LPC_I2C->CONCLR = (I2CONCLR_SIC | I2CONCLR_STAC); //(sec 15.7.6)
		LPC_I2C->CONSET = I2CONSET_STA;                   //(sec 15.7.1)
		
	  //Wait for Start confirmation
		waitForStatusI2C(START); 
	
		LPC_I2C->DAT = address;         //Set Device I2C Address to read from (sec 15.7.3)
		LPC_I2C->CONCLR = I2CONCLR_SIC; //Clear Interrupt (sec 15.7.6)
		
	  // Wait for Read Slave Address ACK
		waitForStatusI2C(SLARACK);
		
		//Read specified number of bytes
		for(i=0; i<bytes-1; i++){
			LPC_I2C->CONSET = I2CONSET_AA;	                //Set Acknowledge (sec 15.7.1)
			LPC_I2C->CONCLR = I2CONCLR_SIC | I2CONCLR_STAC; //Clear Interrupt and Start (sec 15.7.6)
			waitForStatusI2C(DATRACK);                         //Wait for Data Read ACK
			dataBuff[i]=LPC_I2C->DAT;                       //Store the new data (sec 15.7.3)
		}
		
		LPC_I2C->CONCLR = I2CONCLR_SIC | I2CONCLR_AAC;    //Clear Interrupt and Acknowledge (sec 15.7.6)
		waitForStatusI2C(DATRNACK);                          //Wait for Data Read NACK
		dataBuff[i]=LPC_I2C->DAT;                         //Store the new data (sec 15.7.3)
		
		//Done Reading Bytes
		LPC_I2C->CONSET = I2CONSET_STO; //Send Stop Command (sec 15.7.1)
		LPC_I2C->CONCLR = I2CONCLR_SIC; //Clear Interrupt (sec 15.7.6)
		
}



/*
* I2CSend
*
*	Purpose : Send a number of bytes from a buffer over the I2C Data line
*
* Inputs:
*			address  : The address of the chip to send data to
*			bytes		 : The number of bytes to send
*			dataBuff : The buffer containing the data to be sent
*
* Documentation: (sec 15.8)
*
*/
void I2CSend(uint8_t address, uint32_t bytes, uint8_t* dataBuff){

		int i;
		
		//Clear the Interrupt and Start Registers, then send a Start Command
		LPC_I2C->CONCLR = (I2CONCLR_SIC | I2CONCLR_STAC); //(sec 15.7.6)
		LPC_I2C->CONSET = I2CONSET_STA;                   //(sec 15.7.1)
		
	  //Wait for Start confirmation
		waitForStatusI2C(START); 
	
		LPC_I2C->DAT = address;         //Set Device I2C Address (sec 15.7.3)
		LPC_I2C->CONCLR = I2CONCLR_SIC; //Clear Interrupt (sec 15.7.6)
	
		//Wait for Write Slave Address ACK
		waitForStatusI2C(SLAWACK);

		//Send specified number of bytes
		for(i=0; i<bytes; i++){
			LPC_I2C->DAT = dataBuff[i];                     //Set the data to be sent (sec 15.7.3)
			LPC_I2C->CONSET = I2CONSET_AA;                  //Set Acknowledge (sec 15.7.1)
			LPC_I2C->CONCLR = I2CONCLR_SIC | I2CONCLR_STAC; //Clear Interrupt and Start (sec 15.7.6)
			waitForStatusI2C(DATWACK);                         //Wait for Data Write ACK	
		}
		
		//Done Sending Bytes
		LPC_I2C->CONSET = I2CONSET_AA | I2CONSET_STO;     //Set Acknowledge and send Stop Command (sec 15.7.1)
		LPC_I2C->CONCLR = I2CONCLR_SIC ;                  //Clear Interrupt (sec 15.7.6)
}

/*
* I2CInit
*
* Purpose : Initialize I2C controller
*
* Inputs : 
*      I2cMode : Either MASTER or SLAVE
*
*/
void I2CInit(uint32_t I2cMode){

  LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 5);  //enable I2C clock (sec 3.5.14)
  LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 16); //enable IOCON clock (sec 3.5.14)
  LPC_SYSCON->PRESETCTRL |= (1UL << 1);     //enable I2C peripheral (sec 3.5.2)
	
  LPC_IOCON->PIO0_4 &= ~0x303;	//clear register values and select standard fast-mode I2C (sec 7.4.11)
  LPC_IOCON->PIO0_4 |= 0x01;		//set pin as SCL (sec 7.4.11)
  LPC_IOCON->PIO0_5 &= ~0x303;	//clear register values and select standard fast-mode I2C (sec 7.4.12)
  LPC_IOCON->PIO0_5 |= 0x01;		//set pin as SDA (sec 7.4.12)


  //Clear flags (sec 15.7.6)
  LPC_I2C->CONCLR |= I2CONCLR_AAC | I2CONCLR_SIC | I2CONCLR_STAC | I2CONCLR_I2ENC | I2CONCLR_STOC;    

  //Reset register duty cycle values (sec 15.7.5)
  LPC_I2C->SCLL   = I2SCLL_SCLL;
  LPC_I2C->SCLH   = I2SCLH_SCLH; 

  LPC_I2C->CONSET = I2CONSET_I2EN; //enable I2C interface (sec 15.7.1)

}

