/*
 ============================================================================
 Name        : CONTROL_ECU.c
 Author      : Omar Tarek Youssef Kamal
 Description : Final Project (Source file for the CONTROL_ECU APP)
 Date        : 28/10/2021
 ============================================================================
 */

#include "CONTROL_ECU.h"

/*
 * Description : Function to assign the call back function(every interrupt) to of
 *               the Alarm timer (1 minute).
 */
void Tick_Processing(void)
{
	g_Count++;
	if(g_Count == NUMBER_OF_INTTERUPT_PER_SECOND)
	{
		g_Count = 0;
		g_buzz_count++;
		if(g_buzz_count == 60)
		{
			Buzzer(LOGIC_LOW);
			LED(LOGIC_LOW);
			g_buzz_count = 0;
			Timer_DeInit();
		}
	}
}

/*
 * Description : Function to assign the call back function(every interrupt) to of
 *               the motor timer (15 seconds).
 */
void MotorTick_Processing(void)
{
	g_Count2++;
	if(g_Count2 == NUMBER_OF_INTTERUPT_PER_SECOND)
	{
		g_Count2 = 0;
		g_motor_count++;

		if(g_motor_count == 15)
		{
			DcMotor_Rotate(STOP);
		}
		if(g_motor_count == 18)
		{
			DcMotor_Rotate(ACW);
		}
		if(g_motor_count == 33)
		{
			DcMotor_Rotate(STOP);
			g_motor_count=0;
			Timer_DeInit();
		}
	}
}

int main(void) {

	/* Enable Global Interrupt I-Bit */
	SREG |= (1<<7);

	/* Create configuration structure for UART driver */
	UART_ConfigType UART_Config = {ASYNCHRONOUS,DISABLED,ONE_BIT,EIGHT_BIT};

	UART_init(&UART_Config); 	/* initialize UART driver */
	DcMotor_Init(); 			/* initialize DC MOTOR driver */
	LCD_init(); 				/* initialize LCD driver */

	while(1){
		Do_Command();

	}

	return 0;
}

/*
 * Description : Function to Recieve commands from the HMI ECU Using USART.
 *
 */
void Do_Command(void)
{

	command = UART_recieveByte();
	switch(command)
	{
	case EEPROM: //EEPROM
		Save_Password_In_Memory();
		break;
	case MOTOR: //motor
		_delay_ms(300);
		DcMotor_Rotate(CW);
		_delay_ms(300);

		TIMER_ConfigType TIMER_Config = {0,0,F_CPU_1024,OVERFLOW};
		Timer0_init(&TIMER_Config); /* initialize TIMER0 driver */

		//MotorTick_Processing();
		timer_setCallBack(MotorTick_Processing);

		break;
	case BUZZER: //buzzer
		LED(LOGIC_HIGH);
		Buzzer(LOGIC_HIGH);
		TIMER_ConfigType TIMER_Config2 = {0,0,F_CPU_1024,OVERFLOW};
		Timer0_init(&TIMER_Config2); /* initialize TIMER0 driver */
		timer_setCallBack(Tick_Processing);
		break;
	}
}

/*
 * Description : Function to recieve password that is stored in the global array.
 *
 */
void Recieve_Password(uint8 a_arr[])
{
	for(int i=0 ; i<PASSWORD_ARRAY_SIZE ; i++)
	{
		a_arr[i] = UART_recieveByte();
	}
}

/*
 * Description : Function to  store password in the External EEPROM.
 *
 */
void Save_Password_In_Memory(void)
{
	uint8 i;
	Recieve_Password(g_password);
	for(i = 0; i < PASSWORD_ARRAY_SIZE; i++)
	{
		LCD_moveCursor(0,i);
		EEPROM_writeByte(0x0311+i,g_password[i]);  /* Write g_password[i] in the external EEPROM */
		_delay_ms(10);
	}
}

/*
 * Description : Write the value Logic High or Logic Low on the required pin.
 * 				 Setup the direction of the required pin output.
 */
void Buzzer(uint8 value)
{
	BUZZER_setup(value);
}

/*
 * Description : Write the value Logic High or Logic Low on the required pin.
 * 				 Setup the direction of the required pin output.
 */
void LED(uint8 value)
{
	GPIO_setupPinDirection(PORTD_ID, PIN2_ID, PIN_OUTPUT);
	GPIO_writePin(PORTD_ID, PIN2_ID, value);
}


