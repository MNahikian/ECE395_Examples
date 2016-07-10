/*
* PWM Example Program for LPC1114
* ===============================
* This example sets up a PWM signal on R_PIO1_1 (pin 10)
* using 32-bit timers.
*/

#ifndef PWM_32BIT_TIMER
#define PWM_32BIT_TIMER

#include "LPC11xx.h"

#define PWM_BASE_PERIOD 48000000 //Base period to produce a 1Hz signal

void pwm_32bit_timer_init(int pwmFrequency, float dutyCyclePercent);

#endif // PWM_32BIT_TIMER
