/*
 ============================================================================
 Name        : Mini_Project3.c
 Author      : Omar Tarek Youssef Kamal
 Description : Fan Controller System Project
 Date        : 08/10/2021
 ============================================================================
 */

#include "lcd.h"
#include "lm35_sensor.h"
#include "adc.h"
#include "lcd.h"
#include "dc_motor.h"

int main(void) {

	uint8 temp;
	/* Create configuration structure for ICU driver */
	ADC_ConfigType ADC_Config = {ADC_INT_VOLT,PRESCALER_8};

	LCD_init(); 			/* initialize LCD driver */
	ADC_init(&ADC_Config); 	/* initialize ADC driver */
	DcMotor_Init(); 		/* initialize DC MOTOR driver */

	/* Display this string "FAN is " only once on LCD at the first row */
	LCD_displayStringRowColumn(0,2,"FAN is ");
	/* Display this string "Temp =    C" only once on LCD at the second row */
	LCD_displayStringRowColumn(1,2,"Temp =     C");


	while(1)
	{
		temp = LM35_getTemperature();

		/* Display the temperature value every time at same position */
		LCD_moveCursor(0,8);
		if(temp < 30)
		{
			DcMotor_Rotate(STOP,0);
			LCD_displayString(" OFF");
			LCD_moveCursor(1,9);
			LCD_intgerToString(temp);
			LCD_displayCharacter(' ');
		}
		else if(temp >= 30 && temp < 60)
		{
			DcMotor_Rotate(CW,25);
			LCD_displayString(" ON");
			LCD_displayCharacter(' ');
			LCD_moveCursor(1,9);
			LCD_intgerToString(temp);
			LCD_displayCharacter(' ');
		}
		else if(temp >= 60 && temp < 90)
		{
			DcMotor_Rotate(CW,50);
			LCD_displayString(" ON");
			LCD_displayCharacter(' ');
			LCD_moveCursor(1,9);
			LCD_intgerToString(temp);
			LCD_displayCharacter(' ');
		}
		else if(temp >= 90 && temp < 120)
		{
			DcMotor_Rotate(CW,75);
			LCD_displayString(" ON");
			LCD_displayCharacter(' ');
			LCD_moveCursor(1,9);
			LCD_intgerToString(temp);
			LCD_displayCharacter(' ');
		}
		else if(temp >= 120 && temp <= 150)
		{
			DcMotor_Rotate(CW,100);
			LCD_displayString(" ON");
			LCD_displayCharacter(' ');
			LCD_moveCursor(1,9);
			LCD_intgerToString(temp);
			LCD_displayCharacter(' ');
		}
	}
	return 0;
}
