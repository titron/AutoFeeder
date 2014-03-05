################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Source/System/draw/disp_msg.c \
../Source/System/draw/disp_widget.c \
../Source/System/draw/draw_play.c \
../Source/System/draw/draw_set.c \
../Source/System/draw/draw_task.c \
../Source/System/draw/draw_test.c 

OBJS += \
./Source/System/draw/disp_msg.o \
./Source/System/draw/disp_widget.o \
./Source/System/draw/draw_play.o \
./Source/System/draw/draw_set.o \
./Source/System/draw/draw_task.o \
./Source/System/draw/draw_test.o 

C_DEPS += \
./Source/System/draw/disp_msg.d \
./Source/System/draw/disp_widget.d \
./Source/System/draw/draw_play.d \
./Source/System/draw/draw_set.d \
./Source/System/draw/draw_task.d \
./Source/System/draw/draw_test.d 


# Each subdirectory must supply rules for building sources it contributes
Source/System/draw/%.o: ../Source/System/draw/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


