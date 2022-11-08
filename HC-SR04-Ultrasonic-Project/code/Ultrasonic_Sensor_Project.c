/*
 ============================================================================
 Name        : Mini_Project3.c
 Author      : Omar Tarek Youssef Kamal
 Description : Ultrasonic Sensor Project
 Date        : 08/10/2021
 ============================================================================
 */

#include <util/delay.h> /* For the delay functions */
#include "lcd.h"
#include "us.h"
#include <avr/io.h> /* To use the SREG register */

int main(void) {

	uint16 distance = 0;

	/* Enable Global Interrupt I-Bit */
	SREG |= (1<<7);

	LCD_init(); 			/* initialize LCD driver */
	Ultrasonic_init();		/* initialize US driver */

	/* Display this string "Distance= " only once on LCD at the first row */
	LCD_displayStringRowColumn(0,0,"Distance= ");
	LCD_displayStringRowColumn(0,14,"cm");
	LCD_moveCursor(0,10);

	/* Display the Ultrasonic Sensor value every time at same position */
	distance = Ultrasonic_readDistance();
	_delay_ms(5); /* delay for processing 5ms */
	LCD_intgerToString(distance);


	while(1){}

	return 0;
}
