 /******************************************************************************
 *
 * Module: Timer
 *
 * File Name: timer.h
 *
 * Description: Header file for the timer AVR driver
 *
 * Author: Omar Tarek Youssef Kamal
 *
 *******************************************************************************/

#ifndef TIMER_H_
#define TIMER_H_

#include "std_types.h"

/*******************************************************************************
 *                         Configurations                                      *
 *******************************************************************************/

typedef enum
{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024
}Timer_Clock;

typedef enum
{
	OVERFLOW, COMPARE
}Timer_Mode;

typedef struct
{
	uint32 timer_InitialValue;
	uint32 timer_CompareValue;
	Timer_Clock timer_clock;
	Timer_Mode  timer_mode;

}TIMER_ConfigType;
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function to Initialize Timer Driver:
 * Work in Interrupt Mode
 * Timer initial value
 * Timer_Mode (OverFlow, Compare)
 * if using CTC mode: Timer compare match
 * Timer_Prescaler
 */
void Timer0_init(const TIMER_ConfigType * Config_Ptr);

/*
 * Description: Function to set the Call Back function address.
 */
void timer_setCallBack(void(*a_ptr)(void));

/*
 * Description: Function to stop the clock of the timer to stop incrementing.
 */
void Timer_stop();

/*
 * Description: Function to DeInit the timer to start again from beginning.
 */
void Timer_DeInit();

#endif /* TIMER_H_ */
