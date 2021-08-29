
#include <avr/io.h>
#include "std_macros.h"
void ADC_vinit(void)
{
	SET_BIT(ADMUX,REFS0); //configure VREF
	SET_BIT(ADCSRA,ADEN); // enable ADC
	/* adjust ADC clock*/
	SET_BIT(ADCSRA,ADPS2);
	SET_BIT(ADCSRA,ADPS1);
}
double ADC_u16Read(void)
{
	unsigned short read_val;
	
	SET_BIT(ADCSRA,ADSC);
	while(IS_BIT_CLR(ADCSRA,ADIF));//stay in your position till ADIF become 1
	SET_BIT(ADCSRA,ADIF); // clear ADIF
	read_val=(ADCL);
	read_val|=(ADCH<<8);
	//(x - 0) * (0 - 255) / (1 - 0) + 255;
	double return_val = ((double)read_val /(double)1023) *(double)5;
	return return_val ;
}