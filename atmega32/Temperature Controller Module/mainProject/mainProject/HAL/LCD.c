


#include "LCD.h"
#define  F_CPU 8000000UL 
#include <util/delay.h>
#include "LCD_Cfg.h"
static void send_falling_edge(void);

void LCD_vInit(void)
{
	_delay_ms(200);
	for (uint8_t loop = 0; loop < LCD_NUM_OF_DATA_PINS; loop++ )
	{
		DIO_vsetPINDir(LCD_port,LCD_ConfigParameters.DataPinsChannel[loop],1);
	}
	DIO_vsetPINDir(LCD_ConfigParameters.EnableDataChannel.Port,LCD_ConfigParameters.EnableDataChannel.Channel,1);
	DIO_vsetPINDir(LCD_ConfigParameters.ReadWriteChannel.Port,LCD_ConfigParameters.ReadWriteChannel.Channel,1);
	DIO_vsetPINDir(LCD_ConfigParameters.RegisterSelectChannel.Port,LCD_ConfigParameters.RegisterSelectChannel.Channel,1);
	#if defined eight_bits_mode
	DIO_write(LCD_ConfigParameters.ReadWriteChannel.Port,LCD_ConfigParameters.ReadWriteChannel.Channel,0);
	LCD_vSend_cmd(EIGHT_BITS); /*8 bit mode */
	_delay_ms(1);

	#elif defined four_bits_mode
   	DIO_write(LCD_ConfigParameters.ReadWriteChannel.Port,LCD_ConfigParameters.ReadWriteChannel.Channel,0);
	LCD_vSend_cmd(RETURN_HOME); /*return home */
	_delay_ms(10);
	LCD_vSend_cmd(FOUR_BITS); /* 4bit mode */
	_delay_ms(1);
	#endif
	
	LCD_vSend_cmd(CURSOR_OFF_DISPLAN_ON);/* display on cursor on */
	_delay_ms(1);
	LCD_vSend_cmd(CLR_SCREEN);/* clear the screen */
	_delay_ms(10);
	LCD_vSend_cmd(ENTRY_MODE); /* entry mode */
	_delay_ms(1);
}


static void send_falling_edge(void)
{
	DIO_write(LCD_ConfigParameters.EnableDataChannel.Port,LCD_ConfigParameters.EnableDataChannel.Channel,1);
	_delay_ms(2);
	DIO_write(LCD_ConfigParameters.EnableDataChannel.Port,LCD_ConfigParameters.EnableDataChannel.Channel,0);
	_delay_ms(2);
}
void LCD_vSend_cmd(uint8_t cmd)
{
	#if defined eight_bits_mode
	DIO_write_port(LCD_port,cmd);
	DIO_write(LCD_ConfigParameters.RegisterSelectChannel.Port,LCD_ConfigParameters.RegisterSelectChannel.Channel,0);
	send_falling_edge();
	
	#elif defined four_bits_mode
	write_high_nibble(LCD_port,cmd>>4);
	DIO_write(LCD_ConfigParameters.RegisterSelectChannel.Port,LCD_ConfigParameters.RegisterSelectChannel.Channel,0);
	send_falling_edge();
	write_high_nibble(LCD_port,cmd);
	DIO_write(LCD_ConfigParameters.RegisterSelectChannel.Port,LCD_ConfigParameters.RegisterSelectChannel.Channel,0);
	send_falling_edge();
	#endif
	_delay_ms(1);
}

void LCD_vSend_char(int8_t data)
{
	#if defined eight_bits_mode
	DIO_write_port(LCD_port,data);
	DIO_write(LCD_ConfigParameters.RegisterSelectChannel.Port,LCD_ConfigParameters.RegisterSelectChannel.Channel,1);
	send_falling_edge();
	
	#elif defined four_bits_mode
	write_high_nibble(LCD_port,data>>4);
	DIO_write(LCD_ConfigParameters.RegisterSelectChannel.Port,LCD_ConfigParameters.RegisterSelectChannel.Channel,1);
	send_falling_edge();
	write_high_nibble(LCD_port,data);
	DIO_write(LCD_ConfigParameters.RegisterSelectChannel.Port,LCD_ConfigParameters.RegisterSelectChannel.Channel,1);
	send_falling_edge();
	#endif
	_delay_ms(1);
}


void LCD_vSend_string(int8_t *data)
{
	while((*data)!='\0')
	{
		LCD_vSend_char(*data);
		_delay_ms(50);
		data++;
	}
}
void LCD_clearscreen(void)
{
	LCD_vSend_cmd(CLR_SCREEN);
	_delay_ms(10);
}
void LCD_shiftDisplay(uint8_t direction)
{

	if(direction == RIGHT)
	{
		LCD_vSend_cmd(MOVE_RIGHT);
	}
	else if(direction == LEFT)
	{
		LCD_vSend_cmd(MOVE_LEFT);
	}
	else
	{
		
	}
	_delay_ms(1);
}

void LCD_movecursor(uint8_t row,uint8_t coloumn)
{
	int8_t data = 0 ;
	if(row>2||row<1||coloumn>16||coloumn<1)
	{
		data=0x80;
	}
	else if(row==1)
	{
		data=0x80+coloumn-1 ;
	}
	else if (row==2)
	{
		data=0xc0+coloumn-1;
	}
	LCD_vSend_cmd(data);
	_delay_ms(1);
}
