################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Source/Drive/Common/driver_ae1.c \
../Source/Drive/Common/driver_eeprom.c \
../Source/Drive/Common/driver_evolume.c \
../Source/Drive/Common/driver_flash.c \
../Source/Drive/Common/driver_lcd.c \
../Source/Drive/Common/driver_oled.c 

OBJS += \
./Source/Drive/Common/driver_ae1.o \
./Source/Drive/Common/driver_eeprom.o \
./Source/Drive/Common/driver_evolume.o \
./Source/Drive/Common/driver_flash.o \
./Source/Drive/Common/driver_lcd.o \
./Source/Drive/Common/driver_oled.o 

C_DEPS += \
./Source/Drive/Common/driver_ae1.d \
./Source/Drive/Common/driver_eeprom.d \
./Source/Drive/Common/driver_evolume.d \
./Source/Drive/Common/driver_flash.d \
./Source/Drive/Common/driver_lcd.d \
./Source/Drive/Common/driver_oled.d 


# Each subdirectory must supply rules for building sources it contributes
Source/Drive/Common/%.o: ../Source/Drive/Common/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


