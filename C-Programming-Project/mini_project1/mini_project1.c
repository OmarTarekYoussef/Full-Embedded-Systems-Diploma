/*
 ============================================================================
 Name        : Vehicle_Control_system.c
 Author      : Omar Tarek Youssef Kamal Attia
 Data        : 09/09/2021
 Description : Vehicle Control System Project
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

void MainMenu(void);
void Sensors_set_menu(void);
void Traffic_Light(void);
void Room_Temperature(void);
void Engine_Temperature(void);
void view_data(void);

#define WITH_ENGINE_TEMP_CONTROLLER 1

int quit = 0;
int engine_mode = 0;
int Vehicle_speed = 0;
int AC = 0;
int room_Temp = 30;
int ETC = 0;
int engine_Temp = 90;

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	#if WITH_ENGINE_TEMP_CONTROLLER == 1
		printf("welcome, sir!\nPlease select what you need from the list below:\n\n");
		MainMenu();
		if (quit == 0) return 0;

	#else
		printf("The End\n");

	#endif

}

void MainMenu(void)
{
	char input_1;
	printf("\na. Turn on the vehicle engine.\n");
	printf("b. Turn off the vehicle engine.\n");
	printf("c. Quit the system.\n\n");
	scanf(" %c",&input_1);

	switch(input_1)
	{
		case('a'):
			engine_mode = 1;
			printf("The vehicle engine is on now.\n");
			Sensors_set_menu();
			break;
		case('b'):
			MainMenu();
			break;
		case('c'):
			printf("You've quit the program.\n");
			quit = 1;
			break;
		default:
			printf("Invalid choice.\nPlease try again.\n");
			MainMenu();
	}
}

void Sensors_set_menu(void)
{
	char input_2;
	printf("\na. Turn off the vehicle engine.\n");
	printf("b. Set the traffic light color.\n");
	printf("c. Set the room temperature.\n");
	printf("d. Set the engine temperature.\n\n");
	scanf(" %c",&input_2);

	switch(input_2)
	{
		case('a'):
			MainMenu();
			break;
		case('b'):
			Traffic_Light();
			view_data();
			Sensors_set_menu();
			break;
		case('c'):
			Room_Temperature();
			view_data();
			Sensors_set_menu();
			break;
		case('d'):
			Engine_Temperature();
			view_data();
			Sensors_set_menu();
			break;
		default:
			printf("Invalid choice.\nPlease try again.\n");
			Sensors_set_menu();
	}
}

void Traffic_Light(void)
{
	char color;
	printf("Please Enter the required color:");
	scanf(" %c",&color);
	if(color == 'G' || 'g') Vehicle_speed = 100;
	else if(color == 'o' || 'O')
	{
		Vehicle_speed = 30;
		if(AC == 0)
		{
			AC =1;
			room_Temp = (room_Temp * (5/4)) + 1;

		}
		if(ETC == 0)
		{
			ETC =1;
			engine_Temp = (engine_Temp * (5/4)) + 1;
		}
	}
	else if(color == 'R' || 'r') Vehicle_speed = 0;
	else{
		printf("Invalid choice.\nPlease try again");
		Traffic_Light();
	}

}

void Room_Temperature(void)
{
	int r_temp=0;
	printf("Please Enter the required temperature:");
	scanf(" %d",&r_temp);
	if(r_temp < 10 || r_temp > 30){
		AC = 1;
		room_Temp = 20;
	}
	else  AC = 0;
}

void Engine_Temperature()
{
	int e_temp=0;
	printf("Please Enter the required engine temperature:");
	scanf(" %d",&e_temp);
	if(e_temp < 100 || e_temp > 150){
		ETC = 1;
		engine_Temp = 125;
	}
	else  ETC = 0;
}

void view_data(void)
{
	printf("\nVehicle Speed: %d km/hr\n", Vehicle_speed);
	printf("Room temperature: %d c\n", room_Temp);
	printf("Engine temperature: %d c\n", engine_Temp);
	if(engine_mode == 1) printf("Engine is ON\n");
	if(engine_mode == 0) printf("Engine is OFF\n");
	if(AC == 1) printf("AC is ON\n");
	if(AC == 0) printf("AC is OFF\n");
	if(ETC == 1) printf("Engine temperature controller state is ON\n");
	if(ETC == 0) printf("Engine temperature controller state is OFF\n");
}
