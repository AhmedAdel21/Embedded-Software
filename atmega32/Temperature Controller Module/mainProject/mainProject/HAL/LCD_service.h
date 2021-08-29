

#ifndef LCD_SERVICE_H_
#define LCD_SERVICE_H_

#include "LCD.h"

#define  ERROR "ERROR"
#define  STANDBY "STANDBY"
#define  OPERATIONAL "OPERATION"
#define  NORMAL "NORMAL"



void LCD_WelcomeScreen(void);
void LCD_StandbyScreen(void);
void LCD_SetSetTemp(int8_t tempInt);
void LCD_SetCurrentTemp(int8_t CurrentTempInt);
void LCD_SetSystemState(char *State);

#endif /* LCD_SERVICE_H_ */