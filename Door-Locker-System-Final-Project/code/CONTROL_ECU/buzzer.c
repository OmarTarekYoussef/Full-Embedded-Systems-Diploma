 /******************************************************************************
 *
 * Module: Buzzer
 *
 * File Name: buzzer.c
 *
 * Description: Source file for Buzzer driver
 *
 * Author: Omar Tarek Youssef Kamal
 *
 *******************************************************************************/
#include "common_macros.h" /* To use the macros like SET_BIT */
#include "buzzer.h"
#include "gpio.h"
#include "avr/io.h" /* To use the ADC Registers */

/*
 * Description :
 * Setup the direction of the required pin output.
 * Write the value Logic High or Logic Low on the required pin.
 */
void BUZZER_setup(uint8 value)
{
	GPIO_setupPinDirection(BUZZER_PORT_ID, BUZZER_PIN_ID, PIN_OUTPUT);

	if(value == LOGIC_HIGH)
	{
		PORTD |= (1<<3);
	}
	else
	{
		PORTD &= (~(1<<3));
	}
}
