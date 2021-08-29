
#include "std_macros.h"
#include <avr/io.h>
#include <avr/interrupt.h>


void timer_wave_phasecorrectPWM(double x)
{
	/* set OC0 as output pin */
	SET_BIT(DDRB,3);
	/* select phase correct PWM mode*/
	SET_BIT(TCCR0,WGM00);
	/* load a value in OCR0 */
	OCR0=(x - 0) * (0 - 255) / (1 - 0) + 255;
	/* select timer clock */
	CLR_BIT(TCCR0,CS00);
	SET_BIT(TCCR0,CS01);
	CLR_BIT(TCCR0,CS02);
	/* Set OC0 on compare match when up-counting. Clear OC0 on compare match when down counting.*/
	SET_BIT(TCCR0,COM00);
	SET_BIT(TCCR0,COM01);
}
void timer2_overFlow_init_interrupt(void)
{
	/* select CTC mode*/
	CLR_BIT(TCCR2,WGM01);
	CLR_BIT(TCCR2,WGM00);
	/* select timer clock */
	SET_BIT(TCCR2,CS00);
	SET_BIT(TCCR2,CS01);
	CLR_BIT(TCCR2,CS02);
	/* enable interrupt*/
	sei();
	SET_BIT(TIMSK,TOIE2);
}
void timer2_overFlow_stop_interrupt(void){
	CLR_BIT(TIMSK,TOIE2);
}
