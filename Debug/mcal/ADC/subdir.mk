################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../mcal/ADC/ADC.c 

OBJS += \
./mcal/ADC/ADC.o 

C_DEPS += \
./mcal/ADC/ADC.d 


# Each subdirectory must supply rules for building sources it contributes
mcal/ADC/%.o: ../mcal/ADC/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"D:\MobileControlledHome\HAL" -I"D:\MobileControlledHome\HAL\KEYPAD" -I"D:\MobileControlledHome\HAL\LCD" -I"D:\MobileControlledHome\mcal\ADC" -I"D:\MobileControlledHome\mcal\PWM" -I"D:\MobileControlledHome\mcal\TIMER" -I"D:\MobileControlledHome\mcal\UART" -I"D:\MobileControlledHome\mcal\DIO" -I"D:\MobileControlledHome\mcal" -I"D:\MobileControlledHome\UTILS" -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


