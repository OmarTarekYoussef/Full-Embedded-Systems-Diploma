################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Ultrasonic_Sensor_Project.c \
../gpio.c \
../icu.c \
../lcd.c \
../us.c 

OBJS += \
./Ultrasonic_Sensor_Project.o \
./gpio.o \
./icu.o \
./lcd.o \
./us.o 

C_DEPS += \
./Ultrasonic_Sensor_Project.d \
./gpio.d \
./icu.d \
./lcd.d \
./us.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


