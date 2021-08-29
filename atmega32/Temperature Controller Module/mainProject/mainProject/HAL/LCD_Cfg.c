#include "LCD_Cfg.h"
const LCD_ConfigParam LCD_ConfigParameters =
{/*Configuration*/
	{PORT_B,0}, /*Enable data Register config*/
	{PORT_B,1}, /*Register Select config*/
	{PORT_B,2}, /*Read Write config*/
	{
		4,5,6,7 /*Data Pin config*/
	}

};
