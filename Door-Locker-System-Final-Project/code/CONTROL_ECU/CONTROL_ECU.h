 /******************************************************************************
 *
 * Module: CONTROL_ECU
 *
 * File Name: CONTROL_ECU.h
 *
 * Description: Header file for the CONTROL_ECUAPP
 *
 * Author: Omar Tarek Youssef Kamal
 *
 *******************************************************************************/

#ifndef CONTROL_ECU_H_
#define CONTROL_ECU_H_

#include "std_types.h"

/*******************************************************************************
 *                                DRIVERS INCLUDES                             *
 *******************************************************************************/
#include <avr/io.h> /* To use the SREG register */
#include "gpio.h"
#include <util/delay.h> /* For the delay functions */
#include "uart.h"
#include "external_eeprom.h"
#include "buzzer.h"
#include "dc_motor.h"
#include "timer.h"
#include "lcd.h"

/************************************************************************************************
 *                                    DEFINED COMMANDS                                          *
 ************************************************************************************************/
#define EEPROM            0x01
#define MOTOR             0x02
#define BUZZER        	  0x03

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define NUMBER_OF_INTTERUPT_PER_SECOND 32
#define PASSWORD_ARRAY_SIZE 5
uint8 g_Count = 0;
uint8 g_Count2 = 0;
uint8 g_time = 0;
uint8 g_buzz_count = 0;
uint8 g_motor_count = 0;
uint8 command;
uint8 g_password[6];
uint8 check_password[6];

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description : Function to  store password in the External EEPROM.
 *
 */
void Save_Password_In_Memory(void);

/*
 * Description : Function to recieve password that is stored in the global array.
 *
 */
void Recieve_Password(uint8 a_arr[]);

/*
 * Description : Function to Recieve commands from the HMI ECU Using USART.
 *
 */
void Do_Command(void);

/*
 * Description : Function to assign the call back function(every interrupt) to of
 *               the Alarm timer (1 minute).
 *
 */
void Tick_Processing(void);

/*
 * Description : Function to assign the call back function(every interrupt) to of
 *               the motor timer (15 seconds).
 *
 */
void MotorTick_Processing(void);

/*
 * Description : Write the value Logic High or Logic Low on the required pin.
 * 				 Setup the direction of the required pin output.
 *
 */
void Buzzer(uint8 value);

/*
 * Description : Write the value Logic High or Logic Low on the required pin.
 * 				 Setup the direction of the required pin output.
 *
 */
void LED(uint8 value);

#endif /* CONTROL_ECU_H_ */
