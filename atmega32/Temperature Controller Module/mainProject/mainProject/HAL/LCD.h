
#ifndef LCD_H_
#define LCD_H_

#include "LCD_Cfg.h"

void LCD_vInit(void);
void LCD_vSend_cmd(uint8_t cmd);
void LCD_vSend_char(int8_t data);
void LCD_vSend_string(int8_t *data);
void LCD_clearscreen(void);
void LCD_movecursor(uint8_t row,uint8_t coloumn);
void LCD_shiftDisplay(uint8_t direction);

#endif
