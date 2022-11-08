/*
 ============================================================================
 Name        : HMI_ECU.c
 Author      : Omar Tarek Youssef Kamal
 Description : Final Project (Source file for the HMI_ECU APP)
 Date        : 28/10/2021
 ============================================================================
 */

#include "HMI_ECU.h"

/*
 * Description : Function to assign the call back function(every interrupt) to of
 *               the ALERT timer (60 seconds).
 *
 */
void ALERT_Tick_Processing(void)
{
	g_Count++;
	if(g_Count == NUMBER_OF_INTTERUPT_PER_SECOND)
	{
		g_Count = 0;
		g_ALERT_count++;
		if(g_ALERT_count == 5)
		{
			g_ALERT_Tick_flag = 1;
			g_ALERT_count = 0;
			Timer_DeInit();
		}
	}
}

/*
 * Description : Function to assign the call back function(every interrupt) to of
 *               the motor timer (33 seconds).
 *
 */
void DOOR_Tick_Processing(void)
{
	g_Count++;
	if(g_Count == NUMBER_OF_INTTERUPT_PER_SECOND)
	{
		g_Count = 0;
		g_DOOR_count++;
		if(g_DOOR_count == 33)
		{
			g_DOOR_Tick_flag = 1;
			g_DOOR_count = 0;
			Timer_DeInit();
		}
	}
}

int main(void) {

	/* Enable Global Interrupt I-Bit */
	SREG |= (1<<7);

	/* Create configuration structure for UART driver */
	UART_ConfigType UART_Config = {ASYNCHRONOUS,DISABLED,ONE_BIT,EIGHT_BIT};
	UART_init(&UART_Config); 	    /* initialize UART driver */
	LCD_init(); 				    /* initialize LCD driver */

	/* Display this string "DOOR LOCKER SECURITY SYSTEM" on LCD at the beginning */
	LCD_displayStringRowColumn(0,3,"DOOR LOCKER SECURITY SYSTEM");
	/* Display this string "WELCOME" on LCD at the beginning */
	LCD_displayStringRowColumn(1,13,"WELCOME");
	_delay_ms(1000); /* delay for processing 1s */

	Create_Store_Password();

	while(1)
	{
		Main_Options();
	}

	return 0;
}

/*
 * Description : Function to Create and Store password in a global array.
 *
 */
void Create_Store_Password(void)
{
	New_Password();
	_delay_ms(500);
	ReEnter_Password();
	_delay_ms(500);
	Check_ReEnter_Password(g_ReEnter_password);
	sendCommand(EEPROM);
	Send_Password(g_New_password);
}

/*
 * Description : Function to Fill in the new password from the user using the keypad interfacing
 *               and store it in a global array.
 *
 */
void New_Password(void)
{
	uint8 counter = 0;
	LCD_clearScreen();
	/* Display this string "PLEASE ENTER NEW PASSWORD(5)" on LCD */
	LCD_displayStringRowColumn(0,0,"PLEASE ENTER NEW PASSWORD(5)");
	LCD_moveCursor(1,14);
	g_key = KEYPAD_getPressedKey();
	while(g_key != '=')
	{
		g_key = KEYPAD_getPressedKey();
		if( ( g_key != '+' && g_key != '-' && g_key != '*' && g_key != '%' && g_key != '=') || (g_key>= 0 && g_key<= 9) )
		{
			if(counter < PASSWORD_ARRAY_SIZE)
			{
				g_New_password[counter] = g_key;
				LCD_displayCharacter('*');
				counter++;
			}
		}
		_delay_ms(500);
	}
}

/*
 * Description : Function to Fill in the ReEnter password from the user using the keypad interfacing
 *               and store it in a global array.
 *
 */
void ReEnter_Password(void)
{
	uint8 counter = 0;
	LCD_clearScreen();
	/* Display this string "PLEASE RE-ENTER NEW PASSWORD(5)" on LCD */
	LCD_displayStringRowColumn(0,0,"PLEASE RE-ENTER NEW PASSWORD(5)");
	LCD_moveCursor(1,14);
	g_key = KEYPAD_getPressedKey();
	while(g_key != '=')
	{
		g_key = KEYPAD_getPressedKey();
		if( ( g_key != '+' && g_key != '-' && g_key != '*' && g_key != '%' && g_key != '=') || (g_key>= 0 && g_key<= 9) )
		{
			if(counter < PASSWORD_ARRAY_SIZE)
			{
				g_ReEnter_password[counter] = g_key;
				LCD_displayCharacter('*');
				counter++;
			}
		}
		_delay_ms(500);
	}
	_delay_ms(500);
}

/*
 * Description : Function to Fill in the old password from the user using the keypad interfacing
 *               and store it in a global array.
 *
 */
void Fill_Old_Password(void)
{
	uint8 counter = 0;
	g_key = KEYPAD_getPressedKey();
	while(g_key != '=')
	{
		g_key = KEYPAD_getPressedKey();
		if( ( g_key != '+' && g_key != '-' && g_key != '*' && g_key != '%' && g_key != '=') || (g_key>= 0 && g_key<= 9) )
		{
			if(counter < PASSWORD_ARRAY_SIZE)
			{
				check_password[counter] = g_key;
				LCD_displayCharacter('*');
				counter++;
			}
		}
		_delay_ms(500);
	}
	_delay_ms(500);
}

/*
 * Description : Function to Check the ReEnter Password and compare the array with the New Password.
 *
 */
void Check_ReEnter_Password(uint8 a_arr[])
{
	uint8 i;
	for(i = 0; i < PASSWORD_ARRAY_SIZE; i++)
	{
		if(a_arr[i] != g_New_password[i])
		{
			LCD_clearScreen();
			/* Display this string "WRONG PASSWORD!" on LCD */
			LCD_displayStringRowColumn(0,10,"WRONG PASSWORD!");
			_delay_ms(3000);
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,8,"PLEASE TRY AGAIN!");
			_delay_ms(2000);
			Create_Store_Password();
			break;
		}
	}
}

/*
 * Description : Function to Check the old Password.
 *
 */
uint8 Check_Old_Password(uint8 a_arr[])
{
	uint8 i;
	for(i = 0; i < 5; i++)
	{
		if(a_arr[i] != g_New_password[i])
		{
			LCD_clearScreen();
			/* Display this string "WRONG PASSWORD!" on LCD */
			LCD_displayStringRowColumn(0,6,"PASSWORD DON'T MATCH!");
			_delay_ms(3000);
			g_check_flag = 1;
			return 0;
		}
	}
	g_check_flag = 0;
	return 0;
}

/*
 * Description : Function to Send Password to the control ECU Using USART.
 *
 */
void Send_Password(uint8 a_arr[])
{
	uint8 i;

	for(i = 0; i < PASSWORD_ARRAY_SIZE ; i++)
	{
		UART_sendByte(a_arr[i]);
	}
}

/*
 * Description : The main functions of the HMI_ECU that has 2 options either to open the door or
 * 				 to change the password and according to the user decision it send the chosen command
 *               to the control ECU.
 *
 */
void Main_Options(void)
{
	uint8 i;
	LCD_clearScreen();
	/* Display this string "(+): CHANGE PASSWORD" on LCD */
	LCD_displayStringRowColumn(0,6,"(+): OPEN DOOR");
	/* Display this string "(-): OPEN DOOR" on LCD */
	LCD_displayStringRowColumn(1,6,"(-): CHANGE PASSWORD");
	g_key = KEYPAD_getPressedKey();
	switch(g_key)
	{
	case '+':
		LCD_clearScreen();
		/* Display this string "PLEASE ENTER OLD PASSWORD:(5)" on LCD */
		LCD_displayStringRowColumn(0,0,"PLEASE ENTER PASSWORD:(5)");
		LCD_moveCursor(1,14);
		_delay_ms(500);
		Fill_Old_Password();
		Check_Old_Password(check_password);
		Empty_Array();
		for(i = 0; i < 3; i ++)
		{
			if(g_check_flag != 0)
			{
				if(i == 2)
				{
					sendCommand(BUZZER); //buzzer
					_delay_ms(10);
					ALERT_Screen();
					while(g_ALERT_Tick_flag != 1){};
					g_ALERT_Tick_flag = 0;
					Main_Options();
				}
				LCD_clearScreen();
				/* Display this string "PLEASE ENTER OLD PASSWORD:(5)" on LCD */
				LCD_displayStringRowColumn(0,0,"PLEASE ENTER PASSWORD:(5)");
				LCD_moveCursor(1,14);
				_delay_ms(1500);
				Fill_Old_Password();
				Check_Old_Password(check_password);
				Empty_Array();
			}
		}
		sendCommand(MOTOR); //motor
		_delay_ms(10);
		DOOR_Screen();
		while(g_DOOR_Tick_flag != 1){};
		g_DOOR_Tick_flag = 0;
		Main_Options();
		break;

	case '-':
		LCD_clearScreen();
		/* Display this string "PLEASE ENTER OLD PASSWORD:(5)" on LCD */
		LCD_displayStringRowColumn(0,0,"PLEASE ENTER PASSWORD:(5)");
		LCD_moveCursor(1,14);
		_delay_ms(500);
		Fill_Old_Password();
		Check_Old_Password(check_password);
		Empty_Array();
		for(i = 0; i < 3; i ++)
		{
			if(g_check_flag != 0)
			{
				if(i == 2)
				{
					sendCommand(BUZZER); //buzzer
					_delay_ms(10);
					ALERT_Screen();
					while(g_ALERT_Tick_flag != 1){};
					g_ALERT_Tick_flag = 0;
					Main_Options();
				}
				LCD_clearScreen();
				/* Display this string "PLEASE ENTER OLD PASSWORD:(5)" on LCD */
				LCD_displayStringRowColumn(0,0,"PLEASE ENTER PASSWORD:(5)");
				LCD_moveCursor(1,14);
				_delay_ms(1500);
				Fill_Old_Password();
				Check_Old_Password(check_password);
				Empty_Array();
			}
		}
		Create_Store_Password();
		Main_Options();
		break;
	}
}

/*
 * Description : Function to Send commands to the control ECU Using USART.
 *
 */
void sendCommand(uint8 command)
{
	UART_sendByte(command);
}

/*
 * Description : Function to display a message for 1 minute that the user entered a
 *               wrong password for 3 times in row.
 *
 */
void ALERT_Screen(void)
{
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,10,"!!! ALERT !!!");
	LCD_displayStringRowColumn(1,10,"!!! THIEF !!!");

	TIMER_ConfigType TIMER_Config = {0,0,F_CPU_1024,OVERFLOW};
	Timer0_init(&TIMER_Config); /* initialize TIMER0 driver */

	//ALERT_Tick_Processing();
	timer_setCallBack(ALERT_Tick_Processing);
}

/*
 * Description : Function to display a message for 33 Seconds that the motor mode activated.
 *
 */
void DOOR_Screen(void)
{
	/* Display this string "DOOR MODE.." on LCD */
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,12,"DOOR MODE..");

	TIMER_ConfigType TIMER_Config2 = {0,0,F_CPU_1024,OVERFLOW};
	Timer0_init(&TIMER_Config2); /* initialize TIMER0 driver */

	//DOOR_Tick_Processing();
	timer_setCallBack(DOOR_Tick_Processing);
}

/*
 * Description : Function to clear check_password array.
 *
 */
void Empty_Array(void)
{
	uint8 i;
	for(i = 0; i < PASSWORD_ARRAY_SIZE; i++)
	{
		check_password[i] = 0;
	}
}
