 /******************************************************************************
 *
 * Module: Buzzer
 *
 * File Name: buzzer.h
 *
 * Description: header file for Buzzer driver
 *
 * Author: Omar Tarek Youssef Kamal
 *
 *******************************************************************************/

#ifndef BUZZER_H_
#define BUZZER_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define BUZZER_PORT_ID            PORTD_ID
#define BUZZER_PIN_ID             PIN3_ID

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Setup the direction of the required pin output.
 * Write the value Logic High or Logic Low on the required pin.
 */
void BUZZER_setup(uint8 value);

#endif /* BUZZER_H_ */
