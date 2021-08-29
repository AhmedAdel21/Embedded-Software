
#define F_CPU 8000000UL
#include <util/delay.h>
#include "keypad_driver.h"
#include "LCD_service.h"
 void keypad_vInit()
 {
	 DIO_vsetPINDir(PORT_D,0,1);
	 DIO_vsetPINDir(PORT_D,1,1);
	 DIO_vsetPINDir(PORT_D,2,1);
	 DIO_vsetPINDir(PORT_D,3,1);
	 DIO_vsetPINDir(PORT_D,5,0);
	 DIO_vsetPINDir(PORT_D,6,0);
	 DIO_vsetPINDir(PORT_D,7,0);
	 DIO_vconnectpullup(PORT_D,5,1);
	 DIO_vconnectpullup(PORT_D,6,1);
	 DIO_vconnectpullup(PORT_D,7,1);

 }
 char keypad_u8check_press()
 {
	 char arr[4][3]={{'7','8','9'},{'4','5','6'},{'1','2','3'},{'*','0','#'}};
	 char row,coloumn,x;
	 char returnval=NOTPRESSED;
	 for(row=0;row<4;row++)
	 {
		DIO_write(PORT_D,0,1);
		DIO_write(PORT_D,1,1);
		DIO_write(PORT_D,2,1);
		DIO_write(PORT_D,3,1);
		DIO_write(PORT_D,row,0);

		for(coloumn=0;coloumn<3;coloumn++)
		{
			x=DIO_u8read(PORT_D,(coloumn+5));
			if(x==0)
			 {
				 returnval=arr[row][coloumn];
				 break;
			 }
		}
		if(x==0)
		{
			break;
		}
	}

	 return returnval ;
 }

extern int8_t KeypadInput[2];
extern uint8_t arrayIndex;
extern uint8_t clearUnUsedTempFlag;
uint8_t keypadValue(void){
	uint8_t keypadTempValue = keypad_u8check_press();
	static int8_t keypadValue = 0;
	uint8_t keypadFinalValue = keypadNotPressed;
	clearUnUsedTempFlag = 1;
	if (keypadTempValue != NOTPRESSED)
	{
		if (keypadTempValue == '*')
		{
			if (keypadValue!=0)
			{keypadFinalValue = (uint8_t)keypadValue;
			keypadValue=0;}
			else{}
			
		}
		else if(keypadTempValue == '#'){
			keypadFinalValue = KeypadStandBy;
		}
		else
		{
			if (arrayIndex == 2)
			{
				for(uint8_t loop=0;loop<2;loop++){
					KeypadInput[loop]=0;
				}
				arrayIndex = 0;
				}else{}
				KeypadInput[arrayIndex] = keypadTempValue;
				keypadValue = atoi((char *)KeypadInput);
				LCD_SetSetTemp((uint8_t)keypadValue);
				_delay_ms(400);
				arrayIndex++;
				
			}
		}
		else{}
		return keypadFinalValue;
		
	}
