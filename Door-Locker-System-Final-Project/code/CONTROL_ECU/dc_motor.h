 /******************************************************************************
 *
 * Module: DC Motor
 *
 * File Name: dc_motor.h
 *
 * Description: header file for DC Motor driver
 *
 * Author: Omar Tarek Youssef Kamal
 *
 *******************************************************************************/

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "std_types.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum
{
	STOP,CW,ACW
}DcMotor_State;

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define DC_MOTOR1_IN_PORT_ID            PORTB_ID
#define DC_MOTOR1_IN1_PIN_ID            PIN0_ID
#define DC_MOTOR1_IN2_PIN_ID            PIN1_ID

/*
#define DC_MOTOR2_IN_PORT_ID            PORTA_ID
#define DC_MOTOR2_IN3_PIN_ID            PIN0_ID
#define DC_MOTOR2_IN4_PIN_ID            PIN1_ID
*/

/*
#define DC_MOTOR1_EN_PORT_ID            PORTB_ID
#define DC_MOTOR1_EN1_PIN_ID            PIN3_ID
*/

/*
#define DC_MOTOR2_EN_PORT_ID            PORTB_ID
#define DC_MOTOR2_EN2_PIN_ID            PIN2_ID
*/

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for setup the direction for the two motor pins through the GPIO driver.
 */
void DcMotor_Init(void);

/*
 * Description :
 * Function responsible for rotate the DC Motor CW/ or A-CW or stop the motor based on the state input state value.
 */
void DcMotor_Rotate(DcMotor_State state);

#endif /* DC_MOTOR_H_ */
