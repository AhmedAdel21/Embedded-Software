/*
 * sevenSegmentCode.c
 *
 * Created: 4/8/2021 4:20:47 PM
 * Author : DoLa
 */ 
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>


int main(void)
{
    /* Replace with your application code */
	DDRB |= 0xff;
	PORTB |= 0xff; 
	PORTB &= 0b11101000;
	DDRA &= 0x00;
	char pushButtonValue = 0;
	int counter = 0;
	int counter2= 9;
	unsigned char sevenSegmantVlaues[] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x10,0x11}; 

    while (1) 
    {
		
		PORTB |= 0b00100000;
		PORTB &= 0b10111111;
		PORTB &= 0xE8;
		PORTB |= sevenSegmantVlaues[counter];
		
		pushButtonValue = ((PINA&(1<<0))>>0);
		
		if(pushButtonValue == 1){
			_delay_ms(200);
			if(pushButtonValue == 1){
				
				counter++;
				if (counter > 9)
				{
					counter2++;
					if(counter2 > 9){
						counter2=0;
					}
					counter = 0;
				}
				PORTB &= 0xE8;
				PORTB |= sevenSegmantVlaues[counter];
				
			}
		}

		_delay_ms(30);
		PORTB |= 0b01000000;
		PORTB &= 0b11011111;
		PORTB &= 0xE8;
		PORTB |= sevenSegmantVlaues[(counter2)];
		_delay_ms(30);
    }
}

