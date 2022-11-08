 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 * Author: Mohamed Tarek
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
/* UART Driver Baud Rate */
#define USART_BAUDRATE 9600

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum
{
	ASYNCHRONOUS,SYNCHRONOUS
}UART_Mode;

typedef enum
{
	DISABLED = 0, ENABLED_EVEN = 2, ENABLED_ODD = 3
}UART_ParityBit;

typedef enum
{
	ONE_BIT,TWO_BIT
}UART_StopBit;

typedef enum
{
	FIVE_BIT, SIX_BIT, SEVEN_BIT, EIGHT_BIT, NINE_BIT = 7
}UART_CharacterSize;

typedef struct{
	UART_Mode mode;
	UART_ParityBit parity;
	UART_StopBit stop;
	UART_CharacterSize size;
}UART_ConfigType;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_ConfigType * Config_Ptr);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_H_ */
