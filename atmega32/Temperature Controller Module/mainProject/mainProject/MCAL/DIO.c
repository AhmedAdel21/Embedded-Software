

#include <avr/io.h>

#include "DIO.h"
/*start address of each port*/
#define PORTA_BASE_ADDRESS ((uint8_t)0x3B)
#define PORTB_BASE_ADDRESS ((uint8_t)0x38)
#define PORTC_BASE_ADDRESS ((uint8_t)0x35)
#define PORTD_BASE_ADDRESS ((uint8_t)0x32)

/*Port subsystem registers offset*/
#define PORT_REG_OFFSET ((uint8_t)0)
#define DDR_REG_OFFSET ((uint8_t)1)
#define PIN_REG_OFFSET ((uint8_t)2)

#define NUM_OF_PORTS ((uint8_t)4)

/*Registers definitions*/
#define PORT_REG(PORT_ID) (*((volatile  uint8_t*const)(PortBaseAddresses[PORT_ID] - PORT_REG_OFFSET)))
#define DDR_REG(PORT_ID) (*((volatile  uint8_t*const)(PortBaseAddresses[PORT_ID] - DDR_REG_OFFSET)))
#define PIN_REG(PORT_ID) (*((volatile  uint8_t*const)(PortBaseAddresses[PORT_ID] - PIN_REG_OFFSET)))


const uint8_t PortBaseAddresses[NUM_OF_PORTS] ={PORTA_BASE_ADDRESS,
														PORTB_BASE_ADDRESS,
														PORTC_BASE_ADDRESS,
														PORTD_BASE_ADDRESS};
											

void DIO_vsetPINDir(uint8_t portname,uint8_t pinnumber,uint8_t direction)
{

	if(direction==1)
	{
		SET_BIT(DDR_REG(portname),pinnumber);//Set the direction of the given pin in port A as output
	}
	else
	{
		CLR_BIT(DDR_REG(portname),pinnumber);//Set the direction of the given pin in port A as input
	}
}


void DIO_write(uint8_t portname,uint8_t pinnumber,uint8_t outputvalue)

{
	if(outputvalue==1)
	{
		SET_BIT(PORT_REG(portname),pinnumber);//Set the value of the given pin in port A as High
	}
	else
	{
		CLR_BIT(PORT_REG(portname),pinnumber);//Set the value of the given pin in port A as Low
	}

}


uint8_t DIO_u8read(uint8_t portname,uint8_t pinnumber)
{
	uint8_t return_value=0;

	return_value=READ_BIT(PIN_REG(portname),pinnumber);//Read the value from the given pin in port A

	return return_value ;
}
void DIO_toggle(uint8_t portname,uint8_t pinnumber)
{

	TOG_BIT(PORT_REG(portname),pinnumber);//Toggle the value of the given pin in port A
}
void DIO_set_port_direction(uint8_t portname,uint8_t direction)
{

	DDR_REG(portname)=direction; //set the direction of port A
	
}
void DIO_write_port(uint8_t portname,uint8_t portvalue)
{

	PORT_REG(portname)=portvalue; //Write the given value to the port A
}

uint8_t DIO_read_port(uint8_t portname)
{
	uint8_t return_val=0;
	return_val=PIN_REG(portname); // read the value of port A 
	
	return return_val;
}

void DIO_vconnectpullup(uint8_t portname ,uint8_t pinnumber, uint8_t connect_pullup)
{

	if(connect_pullup==1)
	{
		SET_BIT(PORT_REG(portname),pinnumber);
	}
	else
	{
		CLR_BIT(PORT_REG(portname),pinnumber);
	}
		
}

void write_low_nibble(uint8_t portname,uint8_t value)
{
	value &= 0x0f;

	PORT_REG(portname) &= 0xf0;
	PORT_REG(portname) |= value;

}

void write_high_nibble(uint8_t portname,uint8_t value)
{
	value<<=4;
	PORT_REG(portname) &= 0x0f;
	PORT_REG(portname) |= value;

}