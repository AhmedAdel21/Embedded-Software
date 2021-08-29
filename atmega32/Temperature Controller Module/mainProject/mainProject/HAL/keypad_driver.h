
#ifndef KEYPAD_DRIVER_H_
#define KEYPAD_DRIVER_H_
#define NOTPRESSED 200
#include "..\MCAL\DIO.h"

#define keypadNotPressed (uint8_t)250
#define KeypadStandBy (uint8_t)240

void keypad_vInit(void);
char keypad_u8check_press(void);

uint8_t keypadValue(void);


#endif /* KEYPAD_DRIVER_H_ */
