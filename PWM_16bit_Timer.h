/*
* PWM Example Program for LPC1114
* ===============================
* This example sets up a PWM signal on PIO0_8 (pin 1)
* using 16-bit timers.
*/

#ifndef PWM_16BIT_TIMER
#define PWM_16BIT_TIMER

#include "LPC11xx.h"

#define PWM_BASE_PERIOD 48000000 //Base period to produce a 1Hz signal

//IMPORTANT NOTE : You cannot produce signals below 732Hz with 16-bit timers
void pwm_16bit_timer_init(int pwmFrequency, float dutyCyclePercent);

#endif // PWM_16BIT_TIMER
