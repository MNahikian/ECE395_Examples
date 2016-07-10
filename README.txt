// UIUC ECE395 ARM LPC1114 Example Programs
// Mitchell Nahikian - CE'16
// mitchellnahikian@gmail.com
// Summer 2016

//**********************************************************************
* This is the README.txt file for the ECE395 ARM LPC1114 example programs.
* These programs illustrate a proper configuration for the registers on
* the LPC1114 to enable I2C, SPI, and UART communications as well as
* generating PWM signals.
* 
* Note that these examples only include one configuration for each of the
* protocols. Some of the PIO ports used can be substituted for a different
* set of PIO ports depending on your project requirements. See the LPC111X
* data-sheet for alternate port configurations. 
//**********************************************************************

Data-sheets:

	LPC111X User Manual 
		- This contains all of the register and configuration 
		  information for the LPC111X series and is referenced
		  throughout the files as (sec XX.XX.XX).

	MPL115A2 User Manual
		- Contains the communication codes and protocols for 
		  communicating with the device via I2C.
		- This device is used in main.c to illustrate proper use
		  of the I2C Read and Write functions.

	MCP3008 User Manual
		- Contains the communication codes and protocols for 
		  communicating with the device via SPI.
		- This device is used in main.c to illustrate proper use
		  of the SPI Read and Write functions.

Source Files:

	startup_LPC11xx.s
		- Assembly file used in LPC11xx device initializations.
		- Required include in all LPC1114 projects.

	system_LPC11xx.c
		- File used in LPC11xx device initializations.
		- Required include in all LPC1114 projects.

	LPC11xx.h
		- This file is not in the project file path but is included
		  from the C:\Keil_v5\ARM\INC\NXP device directory.
		- Contains structs, definitions, and macros for using the
		  LPC11xx devices.
		- Not strictly required as an include, but it will save you
		  a lot of time and effort interfacing with the device registers.
		- Note that there are different versions of this file and
		  names/values may be different from examples found on the Internet.
	
	main.c
		- Contains usage examples for the functions provided
		  in the following files, as well as supporting 
		  functions for these examples.

	I2C.h
		- Defines macros for selecting the device as Master or Slave
		  as used in the I2CInit function.
		- Defines command macros for the control set and control
		  clear registers used in I2C communication.
		- Defines macros for the high and low register values of
		  the I2C Serial Clock Line duty cycle.
		- Contains function declarations for I2CInit, I2CSend, and
		  I2CRead.

	I2C.c
		- Defines I2C status register values for the I2CSTAT register
		  as described by Tables 235 - 240 in the LPC111X User Manual.
		- Contains function definitions for I2CInit, I2CSend, and
		  I2CRead.
		- Defines the waitForStatusI2C helper function used in I2CSend
		  and I2CRead.

	SPI.h
		-

	SPI.c
		-

	UART.h
		- Declares the UARTInit, sendchar, and getkey functions.

	UART.c
		- Defines the UARTInit function used to initialize the registers
		  for Serial UART communication.
		- Defines the sendchar and getkey helper functions used in Retarget.c.

	Retarget.c
		- Defines function redirection for the system commands fputc, fgetc,
		  ferror, _ttywrch, and _sys_exit.
		- Defines the __FILE struct.

	PWM_16bit_timer.h *ONLY USE FOR FREQUENCIES AT 732Hz AND ABOVE*
		- Defines a macro for the base period to produce a 1Hz signal.
		- Declares the pwm_16bit_timer_init function.

	PWM_16bit_timer.c *ONLY USE FOR FREQUENCIES AT 732Hz AND ABOVE*
		- Defines the pwm_16bit_timer_init function.

	PWM_32bit_timer.h
		- Defines a macro for the base period to produce a 1Hz signal.
		- Declares the pwm_32bit_timer_init function.

	PWM_32bit_timer.c
		- Defines the pwm_32bit_timer_init function.

Usage :

	Each of the provided function sets can be used as shown in main.c
	by including the associated .h file. See the comments in the source files
	for more information on the functions, definitions, and macros.

	Note that the Retarget.c file must be compiled in your project for
	UART communication to work correctly.