#include <c8051f020.h>
#include "std_macros.h"
#include "DIO.h"

//#define Adc_Data		P0  //ADC


 
int ADC_value;


void delay(unsigned int count) 
{
    int i,j;
    for(i=0;i<count;i++)
    for(j=0;j<100;j++);
}





void main()
{
		WDTCN = 0xDE;
		WDTCN = 0xAD;
		DIO_setPortInput(0);

		DIO_setPort_OutPutMode(1,1);


    while(1)
    {
			ADC_value	= DIO_read_port(0);
       DIO_write_port(1,ADC_value);
			
    }
    
}
 