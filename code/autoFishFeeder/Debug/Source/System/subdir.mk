################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Source/System/app_ae1.c \
../Source/System/app_evolume.c \
../Source/System/app_host.c \
../Source/System/app_key.c \
../Source/System/app_menu.c \
../Source/System/main.c \
../Source/System/service_general.c 

OBJS += \
./Source/System/app_ae1.o \
./Source/System/app_evolume.o \
./Source/System/app_host.o \
./Source/System/app_key.o \
./Source/System/app_menu.o \
./Source/System/main.o \
./Source/System/service_general.o 

C_DEPS += \
./Source/System/app_ae1.d \
./Source/System/app_evolume.d \
./Source/System/app_host.d \
./Source/System/app_key.d \
./Source/System/app_menu.d \
./Source/System/main.d \
./Source/System/service_general.d 


# Each subdirectory must supply rules for building sources it contributes
Source/System/%.o: ../Source/System/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


