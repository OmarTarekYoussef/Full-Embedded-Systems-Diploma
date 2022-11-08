 /******************************************************************************
 *
 * Module: HMI_ECU
 *
 * File Name: HMI_ECU.h
 *
 * Description: Header file for the HMI_ECU APP
 *
 * Author: Omar Tarek Youssef Kamal
 *
 *******************************************************************************/

#ifndef HMI_ECU_H_
#define HMI_ECU_H_

#include "std_types.h"

/*******************************************************************************
 *                                DRIVERS INCLUDES                             *
 *******************************************************************************/
#include <util/delay.h> /* For the delay functions */
#include "lcd.h"
#include "keypad.h"
#include "timer.h"
#include "uart.h"
#include <avr/io.h> /* To use the SREG register */

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
uint8 volatile g_flag = 0;
uint8 volatile g_check_flag = 0;
uint8 volatile g_ALERT_Tick_flag = 0;
uint8 volatile g_DOOR_Tick_flag = 0;
uint8 g_key;
uint8 g_New_password[6];
uint8 g_ReEnter_password[6];
uint8 check_password[6];
uint8 g_Count = 0;
uint8 g_ALERT_count = 0;
uint8 g_DOOR_count = 0;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description : Function to Create and Store password in a global array.
 *
 */
void Create_Store_Password(void);

/*
 * Description : The main functions of the HMI_ECU that has 2 options either to open the door or
 * 				 to change the password and according to the user decision it send the chosen command
 *               to the control ECU.
 *
 */
void Main_Options(void);

/*
 * Description : Function to Fill in the new password from the user using the keypad interfacing
 *               and store it in a global array.
 *
 */
void New_Password(void);

/*
 * Description : Function to Fill in the ReEnter password from the user using the keypad interfacing
 *               and store it in a global array.
 */
void ReEnter_Password(void);

/*
 * Description : Function to Send Password to the control ECU Using USART.
 *
 */
void Send_Password(uint8 a_arr[]);

/*
 * Description : Function to Check the ReEnter Password and compare the array with the New Password.
 *
 */
void Check_ReEnter_Password(uint8 a_arr[]);

/*
 * Description : Function to Fill in the old password from the user using the keypad interfacing
                 and store it in a global array.
 *
 */
void Fill_Old_Password(void);

/*
 * Description : Function to Send commands to the control ECU Using USART.
 *
 */
void sendCommand(uint8 command);

/*
 * Description : Function to display a message for 1 minute that the user entered a
 *               wrong password for 3 times in row.
 *
 */
void ALERT_Screen(void);

/*
 * Description : Function to display a message for 33 Seconds that the motor mode activated.
 *
 */
void DOOR_Screen(void);

/*
 * Description : Function to Check the old Password.
 *
 */
uint8 Check_Old_Password(uint8 a_arr[]);

/*
 * Description : Function to clear check_password array.
 *
 */
void Empty_Array(void);

/*
 * Description : Function to assign the call back function(every interrupt) to of
 *               the ALERT timer (60 seconds).
 *
 */
void ALERT_Tick_Processing(void);

/*
 * Description : Function to assign the call back function(every interrupt) to of
 *               the motor timer (33 seconds).
 *
 */
void DOOR_Tick_Processing(void);

#endif /* HMI_ECU_H_ */
