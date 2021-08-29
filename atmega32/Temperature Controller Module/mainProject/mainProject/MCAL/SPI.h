#ifndef SPI_H_
#define SPI_H_
#include <avr/io.h>
/* ----- Constants ----- */
#define SPI_DDR		DDRB
#define SPI_PORT	PORTB
#define SS		4
#define MOSI	5
#define MISO	6
#define SCK		7

#define SPI_SPCR	SPCR
#define SPI_SPDR	SPDR
#define SPI_SPSR	SPSR
#define SPI_SPIF	SPIF
#define SPI_SPE		SPE
#define SPI_MSTR	MSTR
#define SPI_SPR0	SPR0
#define SPI_SPI2X	SPI2X




/* ----- Function prototypes -----*/
void SPI_Init() ;
void SPI_Write(uint8_t data) ;
uint8_t SPI_Read(void) ;

#endif /* SPI_H_ */