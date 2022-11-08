/*
 * stop_watch.c
 *
 *  Created on: Sep 18, 2021
 *      Author: Omar Tarek Youssef Kamal
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned char g_tick_sec = 0;
unsigned char g_tick_min = 0;
unsigned char g_tick_hours = 0;

ISR(TIMER1_COMPA_vect)
{
	g_tick_sec ++;
	if (g_tick_sec == 60){
		g_tick_sec = 0;
		g_tick_min ++;
	}
	if (g_tick_min == 60){
		g_tick_sec = 0;
		g_tick_min = 0;
		g_tick_hours ++;
	}
	if (g_tick_hours == 12){
		g_tick_sec = 0;
		g_tick_min = 0;
		g_tick_hours = 0 ;
	}
}

void Timer1_CTC(void){
	TCNT1 = 0;		/* Set timer1 initial count to zero */
	OCR1A = 1000;
	TIMSK |= (1<<OCIE1A); /* Enable Timer1 Compare A Interrupt */

	/* Configure timer control register TCCR1A
	 * 1. connect OC1A and OC1B  COM1A1=1 COM1A0=1 COM1B0=0 COM1B1=0
	 * 2. FOC1A=1
	 * 3. CTC Mode WGM10=0 WGM11=0 (Mode Number 4)
	 */
	TCCR1A = (1<<FOC1A) | (1<<COM1A0) | (1<<COM1A1);

	/* Configure timer control register TCCR1B
	 * 1. CTC Mode WGM12=1 WGM13=0 (Mode Number 4)
	 * 2. Prescaler = F_CPU/1024 CS10=1 CS11=0 CS12=1
	 */
	TCCR1B = (1<<WGM12) | (1<<CS10) | (1<<CS12);
}

ISR(INT0_vect)
{
	g_tick_sec = 0;
	g_tick_min = 0;
	g_tick_hours = 0;
	/*GIFR |= (1<<INTF0);*/
}

ISR(INT1_vect)
{
	TCCR1B &= ~(1<<CS10) & ~(1<<CS11) & ~(1<<CS12);
	/*GIFR |= (1<<INTF1);*/
}

ISR(INT2_vect)
{
	TCCR1B = (1<<WGM12) | (1<<CS10) | (1<<CS12);
	/*GIFR |= (1<<INTF2);*/
}

void INT0_Init_reset(void)
{
	DDRD  &= (~(1<<PD2));  // Configure INT0/PD2 as input pin
	PORTD |= (1<<PD2);     // Enable the internal pull up resistor at PD2 pin
	GICR  |= (1<<INT0);    // Enable external interrupt pin INT0
	MCUCR |= (1<<ISC01);   // Trigger INT0 with the falling edge
}

void INT1_Init_pause(void)
{
	DDRD  &= (~(1<<PD3));  // Configure INT1/PD3 as input pin
	GICR  |= (1<<INT1);    // Enable external interrupt pin INT1
	MCUCR |= (1<<ISC11) | (1<<ISC10);   // Trigger INT1 with the rasing edge
}

void INT2_Init_resume(void)
{
	DDRB   &= (~(1<<PB2));   // Configure INT2/PB2 as input pin
	PORTB  |= (1<<PB2);      // Enable the internal pull up resistor at PD2 pin
	GICR   |= (1<<INT2);	 // Enable external interrupt pin INT2
	MCUCSR &= (~(1<<ISC2));     // Trigger INT2 with the falling edge
}

int main(){
	DDRC |= 0x0F;
	DDRA |= 0x3F;
	PORTC &= 0xF0;
	PORTA &= 0xC0;
	SREG |= (1<<7);		   // Enable interrupts by setting I-bit
	INT0_Init_reset();
	INT1_Init_pause();
	INT2_Init_resume();
	Timer1_CTC();

	while(1){
			/*SECOND*/
			PORTA = (PORTA & 0xC0) | 0x01;
			PORTC = (PORTC & 0xF0) | (g_tick_sec%10);
			_delay_us(1);

    		PORTA = (PORTA & 0xC0) | 0x02;
    		PORTC = (PORTC & 0xF0) | (g_tick_sec/10);
			_delay_us(1);

			/*MINUTES*/
    		PORTA = (PORTA & 0xC0) | 0x04;
    		PORTC = (PORTC & 0xF0) | (g_tick_min%10);
			_delay_us(1);

    		PORTA = (PORTA & 0xC0) | 0x08;
    	    PORTC = (PORTC & 0xF0) | (g_tick_min/10);
			_delay_us(1);

			/*HOURS*/
    	    PORTA = (PORTA & 0xC0) | 0x10;
    	    PORTC = (PORTC & 0xF0) | (g_tick_hours%10);
			_delay_us(1);


    	    PORTA = (PORTA & 0xC0) | 0x20;
    	    PORTC = (PORTC & 0xF0) | (g_tick_hours/10);
			_delay_us(1);
	}

	return 0;
}
