
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/interrupt.h>
#include ".\HAL\LCD_service.h"
#include ".\HAL\keypad_driver.h"
#include ".\HAL\tc72.h"
#include ".\MCAL\ADC_driver.h"
#include ".\MCAL\timer.h"


uint8_t keypadValue(void);
volatile uint8_t timerCounter = 0;
volatile uint8_t timer = 0;
volatile uint16_t timerThreeMinCounter = 0;
volatile uint8_t timerThreeMinFlag = 0;
volatile uint8_t currentTemp = 25;
volatile int8_t KeypadInput[2]={};
volatile uint8_t arrayIndex = 0;
volatile uint16_t clearUnUsedTempCounter = 0;
volatile uint8_t clearUnUsedTempFlag = 0;
volatile double Vr = 5;
ISR(TIMER2_OVF_vect){
	timerCounter++;
	if (timerCounter % 49 == 0 )
	{
		timer++;
		if (timer %2 == 0)
		{
			currentTemp = tc72_read();
			
		}
		if (timer %5 == 0)
		{
			Vr = ADC_u16Read();
		}
		if(timerThreeMinFlag == 1){
			timerThreeMinCounter++;
		}
		if (clearUnUsedTempFlag==1)
		{
			clearUnUsedTempCounter++;
		}
	}
}


int main(void)
{

	
	uint8_t keypadTempValue = 0;
	uint8_t keypadStartValue = 0;
	char systemState[10] = STANDBY;
	double Vt = 0;
	uint8_t setTempValue = 25;
	double dutycycleValue = 0;
	uint8_t keypadFlag = 1;
	LCD_vInit();
	tc72_Init();
	LCD_WelcomeScreen();
	keypad_vInit();
	ADC_vinit();
	timer2_overFlow_init_interrupt();
	timer_wave_phasecorrectPWM(0);
    while (1) 
    {
		keypadTempValue = keypad_u8check_press();
		if (keypadTempValue != NOTPRESSED)
		{
			keypadStartValue = keypadTempValue;
			keypadTempValue = 0;
			
		}else{}
		if (keypadStartValue == '#')
		{
			if (strcmp(systemState ,OPERATIONAL)!=0)
			{
				LCD_SetSystemState(OPERATIONAL);
				strcpy(systemState, OPERATIONAL);
				LCD_SetSetTemp(setTempValue);
				keypadStartValue=0;
			}
			else{}
				
			while (1){	
			LCD_SetCurrentTemp(currentTemp);		
			if (keypadFlag == 0)
			{	} 
			else
			{										
				if (setTempValue <=currentTemp)
				{
					Vt = 0;
					uint8_t diffTemp = currentTemp - setTempValue;
					if (diffTemp<=5){
						if (strcmp(systemState ,NORMAL)!=0)
						{
							LCD_SetSystemState(NORMAL);
							strcpy(systemState, NORMAL);
							dutycycleValue = 0;
							timer_wave_phasecorrectPWM(dutycycleValue);
							timerThreeMinFlag = 0;
							timerThreeMinCounter=0;
						}
						else
						{
						}
					}
					else if(diffTemp>10){
						if (strcmp(systemState ,ERROR)!=0)
						{
							keypadFlag = 0;
							LCD_SetSystemState(ERROR);
							strcpy(systemState, ERROR);
							timer2_overFlow_stop_interrupt();
					
						}
						else{}
					}
					else{
						keypadFlag = 1;
						dutycycleValue = 0;
						timer_wave_phasecorrectPWM(dutycycleValue);
					}
				}
				
				else
				{
					uint8_t diffTemp = setTempValue - currentTemp;
					if (diffTemp<=5){
						if (strcmp(systemState ,NORMAL)!=0)
						{
							keypadFlag =1;
							dutycycleValue = 0;
							timer_wave_phasecorrectPWM(dutycycleValue);
							LCD_SetSystemState(NORMAL);
							strcpy(systemState, NORMAL);
							timerThreeMinFlag = 0;
							timerThreeMinCounter=0;
						}
						else
						{	}
					}
					else if (diffTemp>5){
						timerThreeMinFlag = 1;
						if (timerThreeMinCounter<=1800)
						{
							keypadFlag=1;
							if (strcmp(systemState ,OPERATIONAL)!=0)
							{
								LCD_SetSystemState(OPERATIONAL);
								strcpy(systemState, OPERATIONAL);
								Vt = ( (double)(setTempValue - currentTemp)/100 ) *10;
								dutycycleValue = ( ( (Vr*2)/10 ) *Vt)/10;
								timer_wave_phasecorrectPWM(dutycycleValue);
							}
							else
							{
								Vt = ( (double)(setTempValue - currentTemp)/100 ) *10;
								dutycycleValue = ( ( (Vr*2.0)/10.0 ) *Vt)/10.0 ;
								timer_wave_phasecorrectPWM(dutycycleValue);
							}
						} 
						else
						{
							if (strcmp(systemState ,ERROR)!=0)
							{
								keypadFlag = 0;
								LCD_SetSystemState(ERROR);
								strcpy(systemState, ERROR);
								timer2_overFlow_stop_interrupt();
								dutycycleValue=0;
								timer_wave_phasecorrectPWM(dutycycleValue);
							}
							else{}
						
						}
					}
				}
			
			uint8_t temp = keypadValue();
			if (temp == keypadNotPressed)
			{	}
			else if(temp == KeypadStandBy){
				LCD_StandbyScreen();
				timer2_overFlow_stop_interrupt();
				dutycycleValue=0;
				timer_wave_phasecorrectPWM(dutycycleValue);
				break;
				
			}
			else
			{ setTempValue = temp;
				LCD_SetSetTemp(setTempValue);
			}
			
			if (clearUnUsedTempCounter >= 200)
			{
				LCD_SetSetTemp(setTempValue);
				for(uint8_t loop=0;loop<2;loop++){
					KeypadInput[loop]=0;
				}
				arrayIndex = 0;
				clearUnUsedTempCounter=0;
				clearUnUsedTempFlag = 0;
			}else{}
		
		} 
				}
				}
		else
		{}		
		
    keypadTempValue = 0;
	}

}