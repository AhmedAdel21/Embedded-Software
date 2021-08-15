#include <c8051f020.h>
#include "std_macros.h"
#include "DIO.h"

//#define Adc_Data		P0  //ADC


sbit ADDC=P2^2;
sbit ADDB=P2^1;
sbit ADDA=P2^0;
sbit ALE=P2^4;
sbit OE=P2^5;
sbit START=P2^6;
sbit EOC=P2^7;
sbit clk=P2^3; 
int ADC_value;

int b ;
int i;
char sig1ON, sig2ON ;
		float sig1 ,sig2;
		float signal_1[3] = {0,0,0};
		float signal_2[3] = {0,0,0};
		float coeff_1[4]={0.349175349616205,
											0.229359258063891,
											0.229359258063891,
											0.349175349616205};
		float coeff_2[4]={-0.641653637485822,
											0.649742213023953,
											0.649742213023953,
											0.641653637485822};


void read_adc() //Function to drive ADC
{
	
    ADC_value=0;
    ALE=0;

    ALE=1;

    OE=1;
		
    ADC_value= DIO_read_port(0);
	

	
}

void adc() 
{

	
	if( sig1ON !=1)
	{
		ADDA=0; // Selecting input channel IN0 using address lines
    read_adc();
    DIO_write_port(1,ADC_value);

	  ADDA=1; // Selecting input channel IN0 using address lines
    read_adc();
    DIO_write_port(3,ADC_value);
		
	
	}
	else
	{
		
		 ADDA=0; // Selecting input channel IN0 using address lines
    read_adc();
    DIO_write_port(1,ADC_value);
		signal_1[i] = ADC_value;
	
	  ADDA=1; // Selecting input channel IN0 using address lines
    read_adc();
    DIO_write_port(3,ADC_value);
		signal_2[i] = ADC_value;
		i++;
		if (i ==4)
		{
			for( b =0 ; b <4 ; b++)
				{
					sig1 += signal_1[3-b] * coeff_1[b];
					sig2 += signal_2[3-b] * coeff_2[b];
				}
				DIO_write_port(1,sig1);
				DIO_write_port(3,sig2);
				sig1 = 0;
				sig2 = 0;
			}
	}
	
	
}




void main()
{
		WDTCN = 0xDE;
		WDTCN = 0xAD;
		DIO_setPortInput(0);
		DIO_setPort_OutPutMode(1,1);
		DIO_setPin_OutPutMode(2,0, 1);
	DIO_setPin_OutPutMode(2,1, 1);
	DIO_setPin_OutPutMode(2,2, 1);
	DIO_setPin_OutPutMode(2,4, 1);
	DIO_setPin_OutPutMode(2, 5, 1);
	DIO_setPinInput(2,6,0);
	
		DIO_setPort_OutPutMode(3,1);
	
		ADDA=0; // Selecting input channel IN0 using address lines
    ADDB=0;
    ADDC=0;
    OE=1;

    while(1)
    {
				sig1ON = DIO_pinRead(2,6);
        adc();
			
			if (i==4)
				i=0;
    
    }
    
}
 