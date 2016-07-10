/*
* PWM Example Program for LPC1114
* ===============================
* This example sets up a PWM signal on PIO0_8 (pin 1)
* using 16-bit timers.
*/

#include "PWM_16bit_Timer.h"

/*
* pwm_16bit_timer_init
*
*	Purpose : Initialize registers to produce a PWM signal
*
* Inputs:
*			pwmFrequency  		: The desired PWM Frequency
*			dutyCyclePercent	: The desired duty cycle percentage
*
* Documentation: (sec 18.7)
*
* IMPORTANT NOTE : You cannot produce signals below 732Hz with 16-bit timers
*
*/

void pwm_16bit_timer_init(int pwmFrequency, float dutyCyclePercent){
	int pwmPeriod = PWM_BASE_PERIOD/pwmFrequency;
	
	LPC_SYSCON->SYSAHBCLKCTRL |= (1UL <<  7);               //enable clocks to 16-bit Counter 0 block
	LPC_SYSCON->SYSAHBCLKCTRL |= (1UL <<  16);              //enable clocks to IOCON block
	
	LPC_IOCON->PIO0_8 |= 0x2;                               //set up pin for PWM use (sec 7.4.23)
  
	LPC_TMR16B0->PR   = 0x0;                                //set prescaler max value, not used here (sec 18.7.4)
  LPC_TMR16B0->MCR  = 0x10;                               //set for reset on counter match (sec 18.7.6)
  LPC_TMR16B0->EMR |= 0x20;                               //set pin 27 to 1 on match (sec 18.7.10)
  LPC_TMR16B0->CCR  = 0;                                  //set to timer mode (sec 18.7.11)
  LPC_TMR16B0->PWMC = 0x1;                                //set channel zero to PWM mode (sec 18.7.12)
  LPC_TMR16B0->MR1  = pwmPeriod;                          //set value for period (sec 18.7.7)
  LPC_TMR16B0->MR0  = (1.0-dutyCyclePercent) * pwmPeriod; //set value for duty cycle (sec 18.7.7)
  LPC_TMR16B0->TCR |= 0x3;                                //enable and reset counter (sec 18.7.2)
  LPC_TMR16B0->TCR &= ~(0x2);                             //clear reset bit (sec 18.7.2)
}
