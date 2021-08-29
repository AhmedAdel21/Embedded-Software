


#define F_CPU 8000000UL

#include <util/delay.h>

#include "LCD_service.h"

void LCD_WelcomeScreen(void){
	int8_t Welcom[] = "WELCOME";
	LCD_movecursor(1,10);
	LCD_vSend_cmd(CURSOR_OFF_DISPLAN_ON);
	LCD_vSend_string(Welcom);
	uint8_t WelcomeScreenCounter=0;
	uint8_t WelcomeScreenRepeat =0;
	for (WelcomeScreenRepeat=0;WelcomeScreenRepeat<3;WelcomeScreenRepeat++)
	{
		for(WelcomeScreenCounter =0;WelcomeScreenCounter<9;WelcomeScreenCounter++){
			_delay_ms(100);
			LCD_shiftDisplay(LEFT);
		}
		for(WelcomeScreenCounter =0;WelcomeScreenCounter<9;WelcomeScreenCounter++){
			_delay_ms(100);
			LCD_shiftDisplay(RIGHT);
		}
	}
	LCD_StandbyScreen();
}
void LCD_StandbyScreen(void){
	LCD_vSend_cmd(CLR_SCREEN);
	int8_t SetTempArray[]="SET:##";
	int8_t CurrentTempArray[]="CRT:##";
	int8_t SystemStateArray[] = "STATE:STANDBY";
	LCD_movecursor(1,1);
	LCD_vSend_string(SetTempArray);
	LCD_movecursor(1,10);
	LCD_vSend_string(CurrentTempArray);
	LCD_movecursor(2,1);
	LCD_vSend_string(SystemStateArray);
}
void LCD_SetSetTemp(int8_t tempInt){
	int8_t col = 5;
	for (int8_t loop = 5;loop<7;loop++)
	{
		LCD_movecursor(1,loop);
		LCD_vSend_char((int8_t)' ');
	}
	LCD_movecursor(1,col);
	
	char CurrentTempString[4];
	itoa(tempInt,CurrentTempString,10);
	if((tempInt/(int8_t)10) == 0){
		LCD_vSend_char('0');
		LCD_vSend_string((int8_t *)CurrentTempString);
	}
	else{
		LCD_vSend_string((int8_t *)CurrentTempString);
	}

}
void LCD_SetCurrentTemp(int8_t CurrentTempInt){
	LCD_movecursor(1,14);
	char CurrentTempString[4];
	itoa(CurrentTempInt,CurrentTempString,10);
	if((CurrentTempInt/(int8_t)10) == 0){
		LCD_vSend_char('0');
		LCD_vSend_string((int8_t *)CurrentTempString);
	}
	else{
		LCD_vSend_string((int8_t *)CurrentTempString);
	}
}
void LCD_SetSystemState(char *State){
	//unsigned char prevState = 
	for (uint8_t loop = 7; loop < 17; loop++)
	{
		LCD_movecursor(2,loop);
		LCD_vSend_char((int8_t)' ');
	}
	LCD_movecursor(2,7);
	LCD_vSend_string((int8_t *)State);
}
