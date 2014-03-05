################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Source/Drive/R8C/driver_clock.c \
../Source/Drive/R8C/driver_csi0.c \
../Source/Drive/R8C/driver_csi1.c \
../Source/Drive/R8C/driver_iic.c \
../Source/Drive/R8C/driver_int.c \
../Source/Drive/R8C/driver_key.c \
../Source/Drive/R8C/driver_led.c \
../Source/Drive/R8C/driver_power.c \
../Source/Drive/R8C/driver_reset.c \
../Source/Drive/R8C/driver_rotary.c \
../Source/Drive/R8C/driver_timer0.c \
../Source/Drive/R8C/driver_timer1.c \
../Source/Drive/R8C/driver_watchdog.c \
../Source/Drive/R8C/fvector.c \
../Source/Drive/R8C/heap.c \
../Source/Drive/R8C/initsct.c \
../Source/Drive/R8C/intprg.c \
../Source/Drive/R8C/mcu_depend.c \
../Source/Drive/R8C/resetprg.c 

OBJS += \
./Source/Drive/R8C/driver_clock.o \
./Source/Drive/R8C/driver_csi0.o \
./Source/Drive/R8C/driver_csi1.o \
./Source/Drive/R8C/driver_iic.o \
./Source/Drive/R8C/driver_int.o \
./Source/Drive/R8C/driver_key.o \
./Source/Drive/R8C/driver_led.o \
./Source/Drive/R8C/driver_power.o \
./Source/Drive/R8C/driver_reset.o \
./Source/Drive/R8C/driver_rotary.o \
./Source/Drive/R8C/driver_timer0.o \
./Source/Drive/R8C/driver_timer1.o \
./Source/Drive/R8C/driver_watchdog.o \
./Source/Drive/R8C/fvector.o \
./Source/Drive/R8C/heap.o \
./Source/Drive/R8C/initsct.o \
./Source/Drive/R8C/intprg.o \
./Source/Drive/R8C/mcu_depend.o \
./Source/Drive/R8C/resetprg.o 

C_DEPS += \
./Source/Drive/R8C/driver_clock.d \
./Source/Drive/R8C/driver_csi0.d \
./Source/Drive/R8C/driver_csi1.d \
./Source/Drive/R8C/driver_iic.d \
./Source/Drive/R8C/driver_int.d \
./Source/Drive/R8C/driver_key.d \
./Source/Drive/R8C/driver_led.d \
./Source/Drive/R8C/driver_power.d \
./Source/Drive/R8C/driver_reset.d \
./Source/Drive/R8C/driver_rotary.d \
./Source/Drive/R8C/driver_timer0.d \
./Source/Drive/R8C/driver_timer1.d \
./Source/Drive/R8C/driver_watchdog.d \
./Source/Drive/R8C/fvector.d \
./Source/Drive/R8C/heap.d \
./Source/Drive/R8C/initsct.d \
./Source/Drive/R8C/intprg.d \
./Source/Drive/R8C/mcu_depend.d \
./Source/Drive/R8C/resetprg.d 


# Each subdirectory must supply rules for building sources it contributes
Source/Drive/R8C/%.o: ../Source/Drive/R8C/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


