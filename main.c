#include "driver_config.h"
#include <stdio.h>
#include "LPC11xx.h"
#include "PWM_32bit_Timer.h"
#include "I2C.h"
#include "UART.h"
#include "SPI.h"
#include "timer32.h"


//The following functions and definitions are used to communicate with the MPL115A2 chip
//They illustrate an example of how to use the I2C functions to communicate with a device
#define COEFFNUM 4
#define MPL115A2_COEFFICIENT 0x04
#define MPL115A2_SLAVEADDRREAD  0xC1
#define MPL115A2_SLAVEADDRWRITE 0xC0
/*
* sendGetCoefficients (MPL115A2)
*
*	Purpose : Send the get coefficient command bytes over I2C and store the results in a buffer
*
* Inputs:
*			rawCoefficients : The destination buffer for the coefficient values of the sensor
*
*/
void sendGetCoefficients(uint8_t* rawCoefficients){
		uint8_t temp[1] = {MPL115A2_COEFFICIENT};
		I2C_Send(MPL115A2_SLAVEADDRWRITE, 1, temp);
		I2C_Read(MPL115A2_SLAVEADDRREAD, COEFFNUM*2, rawCoefficients);
}

/*
* getCoeff (MPL115A2)
*
*	Purpose : Send the get coefficient command to the specified chip
*
* Inputs:
*			chipNum      : The index number of the MPL115A2 chip to send a get coefficients command to
*			coefficients : The destination buffer for the coefficients of the sensor
*
*/


void getCoeff(){
	uint8_t tempCoeff[COEFFNUM*2];
	
	sendGetCoefficients(tempCoeff);
	printf("Coefficients from MPL115A2:\n\r");
	printf("%2x\n\r", (tempCoeff[0] << 8) | tempCoeff[1]);
	printf("%2x\n\r", (tempCoeff[2] << 8) | tempCoeff[3]);
	printf("%2x\n\r", (tempCoeff[4] << 8) | tempCoeff[5]);
	printf("%2x\n\r", (tempCoeff[6] << 8) | tempCoeff[7]);	
}


//The following functions and definitions are used to communicate with the MCP3008 chip
//They illustrate an example of how to use the SPI functions to communicate with a device
#define START_SINGLE 0x1800
#define CHANNEL_MASK 0x07

/*
* getAnalogData (MCP3008)
*
*	Purpose : Read the current analog value
*
* Inputs:
*			channelNum   :   The single-ended channel number to get data from
*	
* Returns: A uint8_t containing a digital representation of the analog value sampled
*/

uint8_t getAnalogData(uint8_t channelNum){
	uint16_t command = (START_SINGLE | ((channelNum & CHANNEL_MASK) << 8));
	SPI_Send(command);
	return SPI_Read();
}



int main(){
	//pwm_32bit_timer_init(50, 0.5);    //Initialize a 50Hz PWM signal with 50% duty cycle
	UART_Init();                      //Initialize UART serial communication
	I2C_Init(I2CMASTER);              //Initialize I2C communication
	SPI_Init();												//Initialize SPI communication
	
	printf("UART is working.\n\r");  //UART test with printf()
  getCoeff();                      //Use I2C functions to request and retrieve data from a MPL115A2
	
	while(1){
		//Use SPI functions to read an analog signal from channel 7
		printf("Analog Data: %x\n\r", (0x7F & getAnalogData(0x07)));
		getCoeff();
	}
	
	return 0;
}
