/*
* PWM Example Program for LPC1114
* ===============================
* This example sets up a PWM signal on R_PIO1_1 (pin 10)
* using 32-bit timers.
*/

#include "PWM_32bit_Timer.h"

/*
* pwm_32bit_timer_init
*
*	Purpose : Initialize registers to produce a PWM signal
*
* Inputs:
*			pwmFrequency  		: The desired PWM Frequency
*			dutyCyclePercent	: The desired duty cycle percentage
*
* Documentation: (sec 20.7)
*
*/
void pwm_32bit_timer_init(int pwmFrequency, float dutyCyclePercent){
	int pwmPeriod = PWM_BASE_PERIOD/pwmFrequency;
	
	LPC_SYSCON->SYSAHBCLKCTRL |= (1UL <<  10);              //enable clocks to 32-bit Counter 1 block (sec 3.5.14)
	LPC_SYSCON->SYSAHBCLKCTRL |= (1UL <<  16);              //enable clocks to IOCON block (sec 3.5.14)
	
	LPC_IOCON->R_PIO1_1 |= 0x3;                             //set up pin for PWM use (sec 7.4.30)
  
	LPC_TMR32B1->PR   = 0x0;                                //set prescaler max value, not used here (sec 18.7.4)
  LPC_TMR32B1->MCR  = 0x400;                              //set for reset on counter match (sec 20.7.6)
  LPC_TMR32B1->EMR |= 0x20;                               //set pin 27 to 1 on match (sec 20.7.10)
  LPC_TMR32B1->CCR  = 0;                                  //set to timer mode (sec 20.7.11)
  LPC_TMR32B1->PWMC = 0x1;                                //set channel zero to PWM mode (sec 20.7.12)
  LPC_TMR32B1->MR3  = pwmPeriod;                          //set value for period (sec 20.7.7)
  LPC_TMR32B1->MR0  = (1.0-dutyCyclePercent) * pwmPeriod; //set value for duty cycle (sec 20.7.7)
  LPC_TMR32B1->TCR |= 0x3;                                //enable and reset counter (sec 20.7.2)
  LPC_TMR32B1->TCR &= ~(0x2);                             //clear reset bit (sec 20.7.2)
}
