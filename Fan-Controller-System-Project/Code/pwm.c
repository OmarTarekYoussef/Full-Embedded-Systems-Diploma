 /******************************************************************************
 *
 * Module: PWM
 *
 * File Name: pwm.c
 *
 * Description: source file for the PWM driver
 *
 * Author: Omar Tarek Youssef Kamal
 *
 *******************************************************************************/

#include "avr/io.h" /* To use the ADC Registers */
#include "common_macros.h" /* To use the macros like SET_BIT */
#include "pwm.h"
#include "gpio.h"

/*
 * Description :
 * Function responsible for trigger the Timer0 with the PWM Mode.
 */
void PWM_Timer0_Start(uint8 duty_cycle)
{
	TCNT0 = 0; //Set Timer Initial value
	OCR0  = ((255*duty_cycle)/100); // Set Compare Value

	/*set PB3/OC0 as output pin --> pin where the PWM signal is generated from MC.*/
	GPIO_setupPinDirection(PWM_OC0_PORT_ID,PWM_OC0_PIN_ID,PIN_OUTPUT);


	/* Configure timer control register
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/8 CS00=0 CS01=1 CS02=0
	 */
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);
}

