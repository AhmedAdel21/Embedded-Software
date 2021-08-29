

#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_
#define four_bits_mode
/* #define eight_bits_mode */

#define CLR_SCREEN 0x01
#define CURSOR_ON_DISPLAN_ON 0x0e
#define CURSOR_OFF_DISPLAN_ON 0x0c
#define RETURN_HOME 0x02
#define ENTRY_MODE 0x06
#define RIGHT 1
#define LEFT 0
#define MOVE_RIGHT 0x1C
#define MOVE_LEFT 0x18
#if defined four_bits_mode
#define LCD_NUM_OF_DATA_PINS ((uint8_t)4)
#define FOUR_BITS 0x28

#elif defined eight_bits_mode
#define LCD_NUM_OF_DATA_PINS ((uint8_t)8)
#define EIGHT_BITS 0x38

#endif

#include "..\MCAL\DIO.h"
struct LCD_ConfigRegister
{
	uint8_t Port;
	uint8_t Channel;
};

#define LCD_port PORT_A
typedef struct
{
	struct LCD_ConfigRegister EnableDataChannel;
	struct LCD_ConfigRegister RegisterSelectChannel;
	struct LCD_ConfigRegister ReadWriteChannel;
	uint8_t DataPinsChannel[LCD_NUM_OF_DATA_PINS];
}LCD_ConfigParam;
extern const LCD_ConfigParam LCD_ConfigParameters;
#endif /* LCD_CONFIG_H_ */
