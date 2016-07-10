/*
* Simple I2C initialization and communication functions
*/

#ifndef I2C
#define I2C   

#include <stdint.h>

#define I2CMASTER	0x01
#define I2CSLAVE  0x02

/* I2C Control Set Register */
#define I2CONSET_I2EN   (0x1<<6)  
#define I2CONSET_AA     (0x1<<2)
#define I2CONSET_SI     (0x1<<3)
#define I2CONSET_STO    (0x1<<4)
#define I2CONSET_STA    (0x1<<5)

/* I2C Control clear Register */
#define I2CONCLR_AAC    (0x1<<2) 
#define I2CONCLR_SIC    (0x1<<3)
#define I2CONCLR_STOC   (0x1<<4)
#define I2CONCLR_STAC   (0x1<<5)
#define I2CONCLR_I2ENC  (0x1<<6)

#define I2SCLH_SCLH			0x00000031  /* I2C SCL Duty Cycle High Reg */
#define I2SCLL_SCLL			0x00000031  /* I2C SCL Duty Cycle Low Reg */

void I2CInit(uint32_t I2cMode);
void I2CSend(uint8_t address, uint32_t bytes, uint8_t* dataBuff);
void I2CRead(uint8_t address, uint32_t bytes, uint8_t* dataBuff);

#endif // I2C
