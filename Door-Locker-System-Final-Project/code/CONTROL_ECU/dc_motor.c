 /******************************************************************************
 *
 * Module: DC Motor
 *
 * File Name: dc_motor.c
 *
 * Description: source file for DC Motor driver
 *
 * Author: Omar Tarek Youssef Kamal
 *
 *******************************************************************************/

#include "common_macros.h" /* To use the macros like SET_BIT */
#include "dc_motor.h"
#include "gpio.h"
#include "pwm.h"

/*
 * Description :
 * Function responsible for setup the direction for the two motor pins through the GPIO driver.
 */
void DcMotor_Init(void)
{
	/* Configure the direction for RS, RW and E pins as output pins */
	GPIO_setupPinDirection(DC_MOTOR1_IN_PORT_ID,DC_MOTOR1_IN1_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR1_IN_PORT_ID,DC_MOTOR1_IN2_PIN_ID,PIN_OUTPUT);
	GPIO_writePin(DC_MOTOR1_IN_PORT_ID, DC_MOTOR1_IN1_PIN_ID, LOGIC_LOW);
	GPIO_writePin(DC_MOTOR1_IN_PORT_ID, DC_MOTOR1_IN2_PIN_ID, LOGIC_LOW);
}

/*
 * Description :
 * Function responsible for rotate the DC Motor CW/ or A-CW or stop the motor based on the state input state value.
 */
void DcMotor_Rotate(DcMotor_State state)
{

	/* check if the state is clock wise/not */
	if(state == CW)
	{
		// Rotate the motor --> clock wise
		GPIO_writePin(DC_MOTOR1_IN_PORT_ID, DC_MOTOR1_IN1_PIN_ID, LOGIC_LOW);
		GPIO_writePin(DC_MOTOR1_IN_PORT_ID, DC_MOTOR1_IN2_PIN_ID, LOGIC_HIGH);
	}

	/* check if the state is anti-clock wise/not */
	else if(state == ACW)
	{
		// Rotate the motor --> anti-clock wise
		GPIO_writePin(DC_MOTOR1_IN_PORT_ID, DC_MOTOR1_IN1_PIN_ID, LOGIC_HIGH);
		GPIO_writePin(DC_MOTOR1_IN_PORT_ID, DC_MOTOR1_IN2_PIN_ID, LOGIC_LOW);
	}

	/* check if the state is Stop/not */
	else if(state == STOP)
	{
		// Stop the motor
		GPIO_writePin(DC_MOTOR1_IN_PORT_ID, DC_MOTOR1_IN1_PIN_ID, LOGIC_LOW);
		GPIO_writePin(DC_MOTOR1_IN_PORT_ID, DC_MOTOR1_IN2_PIN_ID, LOGIC_LOW);
	}



}
