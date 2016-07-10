#include <stdio.h>
#include "LPC11xx.h"
#include "PWM_32bit_Timer.h"
#include "I2C.h"
#include "UART.h"


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
		I2CSend(MPL115A2_SLAVEADDRWRITE, 1, temp);
		I2CRead(MPL115A2_SLAVEADDRREAD, COEFFNUM*2, rawCoefficients);
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

int main(){
	pwm_32bit_timer_init(50, 0.5);   //Initialize a 50Hz PWM signal with 50% duty cycle
	UARTInit();                      //Initialize UART serial communication
	I2CInit(I2CMASTER);              //Initialize I2C communication
	
	printf("UART is working.\n\r");  //UART test with printf()
  getCoeff();                      //Use I2C functions to request and retrieve data from a MPL115A2
	return 0;
}
