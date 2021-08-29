
#include "tc72.h"
#define F_CPU 8000000UL
#include <util/delay.h>
#include "..\MCAL\std_macros.h"
#include "..\MCAL\SPI.h"

void tc72_Init(void){
	SPI_Init();
	SET_BIT(SPI_PORT , SS);
	
	/*Select Control Register*/
	SPI_Write(0x80);
	
	/*Select Continuous temperature Conversion*/
	SPI_Write(0x40);
	
	CLR_BIT(SPI_PORT , SS);
	
	_delay_ms(150);
}

char tc72_read(void){
	char LSB = 0;		/* store temperature value */
	char MSB = 0;
	char tempValue = 0;
	/* ----------- LSB ---------- */
			
	SET_BIT(SPI_PORT , SS);
	SPI_Write(0x01);
	SPI_Write(0x00);
	CLR_BIT(SPI_PORT , SS);
			
	_delay_ms(1);
	LSB = SPI_Read();
	
	/* ----------- MSB ---------- */
			
	SET_BIT(SPI_PORT , SS);
	SPI_Write(0x02);			/* read will be from MSB temperature register */
	SPI_Write(0x00);
	CLR_BIT(SPI_PORT , SS);
			
	_delay_ms(1);
	MSB = SPI_Read();
	
	LSB >>= 7;
	MSB <<= 1;
	tempValue = MSB | LSB;
	return tempValue;
}