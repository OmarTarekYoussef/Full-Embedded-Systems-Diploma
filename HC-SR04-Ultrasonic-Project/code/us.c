 /******************************************************************************
 *
 * Module: Ultrasonic Sensor
 *
 * File Name: us.h
 *
 * Description: Source file for the Ultrasonic Sensor driver
 *
 * Author: Omar Tarek Youssef Kamal
 *
 *******************************************************************************/

#include <util/delay.h> /* For the delay functions */
#include "common_macros.h" /* To use the macros like SET_BIT */
#include "us.h"
#include "icu.h"
#include "gpio.h"

uint8 g_edgeCount = LOGIC_LOW;
uint16 g_timePeriod = LOGIC_LOW;

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/


/*
 * Description :
 * This is the call back function called by the ICU driver.
 * This is used to calculate the high time (pulse time) generated by the ultrasonic sensor.
 */
void Ultrasonic_edgeProcessing(void)
{
	g_edgeCount++;
	if(g_edgeCount == 1)
	{
		/*
		 * Clear the timer counter register to start measurements from the
		 * first detected rising edge
		 */
		Icu_clearTimerValue();

		/* Detect falling edge */
		Icu_setEdgeDetectionType(FALLING);
	}

	if(g_edgeCount == 2)
	{
		/* Store the Period time value */
		g_timePeriod = Icu_getInputCaptureValue();

		/* Clear the timer counter register to start measurements again */
		Icu_clearTimerValue();

		/* Detect rising edge */
		Icu_setEdgeDetectionType(RISING);

		Icu_DeInit(); /* Disable ICU Driver */
	}

}

/*
 * Description :
 * 1.Initialize the ICU driver as required.
 * 2. Setup the ICU call back function.
 * 3. Setup the direction for the trigger pin as output pin through the GPIO driver.
 */
void Ultrasonic_init(void)
{
	/* Create configuration structure for ICU driver */
	Icu_ConfigType Icu_Config = {F_CPU_8,RISING};

	Icu_init(&Icu_Config);	/* initialize ICU driver */

	/* Set the Call back function pointer in the ICU driver */
	Icu_setCallBack(Ultrasonic_edgeProcessing);
	
	/* Configure the direction for Trigger pin as output pins */
	GPIO_setupPinDirection(US_TRIGGER_PORT_ID, US_TRIGGER_PIN_ID, PIN_OUTPUT);
}

/*
 * Description :
 * Send the Trigger pulse to the ultrasonic.
 */
void Ultrasonic_Trigger(void)
{
	GPIO_writePin(US_TRIGGER_PORT_ID, US_TRIGGER_PIN_ID, LOGIC_HIGH);
	_delay_ms(10); /* delay for processing 10us */
	GPIO_writePin(US_TRIGGER_PORT_ID, US_TRIGGER_PIN_ID, LOGIC_LOW);
}

/*
 * Description :
 * Send the trigger pulse by using Ultrasonic_Trigger function.
 * Start the measurements by the ICU from this moment.
 */
uint16 Ultrasonic_readDistance(void)
{
	uint16 dis = LOGIC_LOW;

	/* Send the trigger pulse by using Ultrasonic_Trigger function. */
	Ultrasonic_Trigger();

	dis = g_timePeriod/58.8;
	return dis;
}


