#include <avr/io.h>
#include "std_macros.h"
#include "SPI.h"

/* SPI Initialization */
void SPI_Init(void)
{
	SPI_DDR |= ( (uint8_t)1 << MOSI ) | ( (uint8_t)1 << SCK ) | ( (uint8_t)1 << SS );
	CLR_BIT(SPI_DDR, MISO);
	SPCR |= ( (uint8_t)1 << SPE ) | ( (uint8_t)1 << MSTR ) | ( (uint8_t)1 << SPR0 );
	SPSR &= ~((uint8_t)1 << SPI2X);     /* Disable speed doubler */
}

/* SPI write data */
void SPI_Write(uint8_t data)
{
	SPDR = data;
	while((uint8_t)(!(SPSR & ((uint8_t)1 << SPIF))))
	{
		/* Wait till transmission complete */
	}
}

/* SPI read data */
uint8_t SPI_Read(void)
{
	while(!((uint8_t)SPSR & ((uint8_t)1 << (uint8_t)SPIF)))
	{
		/* Wait till reception complete */
	}
	return SPDR;
}
