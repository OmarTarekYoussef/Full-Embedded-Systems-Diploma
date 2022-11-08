 /******************************************************************************
 *
 * Module: PWM
 *
 * File Name: pwm.h
 *
 * Description: header file for the PWM driver
 *
 * Author: Omar Tarek Youssef Kamal
 *
 *******************************************************************************/

#ifndef PWM_H_
#define PWM_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define PWM_OC0_PORT_ID                 PORTB_ID
#define PWM_OC0_PIN_ID               	PIN3_ID

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for trigger the Timer0 with the PWM Mode.
 */
void PWM_Timer0_Start(uint8 duty_cycle);

#endif /* PWM_H_ */
