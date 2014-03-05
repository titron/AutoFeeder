################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Source/Interface/if_disp.c \
../Source/Interface/if_evolume.c \
../Source/Interface/if_iic.c \
../Source/Interface/if_key.c \
../Source/Interface/if_lcd.c \
../Source/Interface/if_lcd_draw.c \
../Source/Interface/if_lcd_text.c \
../Source/Interface/if_led.c \
../Source/Interface/if_power.c \
../Source/Interface/if_reset.c \
../Source/Interface/if_rotary.c \
../Source/Interface/if_serial_ae1.c \
../Source/Interface/if_serial_flash.c \
../Source/Interface/if_timer.c 

OBJS += \
./Source/Interface/if_disp.o \
./Source/Interface/if_evolume.o \
./Source/Interface/if_iic.o \
./Source/Interface/if_key.o \
./Source/Interface/if_lcd.o \
./Source/Interface/if_lcd_draw.o \
./Source/Interface/if_lcd_text.o \
./Source/Interface/if_led.o \
./Source/Interface/if_power.o \
./Source/Interface/if_reset.o \
./Source/Interface/if_rotary.o \
./Source/Interface/if_serial_ae1.o \
./Source/Interface/if_serial_flash.o \
./Source/Interface/if_timer.o 

C_DEPS += \
./Source/Interface/if_disp.d \
./Source/Interface/if_evolume.d \
./Source/Interface/if_iic.d \
./Source/Interface/if_key.d \
./Source/Interface/if_lcd.d \
./Source/Interface/if_lcd_draw.d \
./Source/Interface/if_lcd_text.d \
./Source/Interface/if_led.d \
./Source/Interface/if_power.d \
./Source/Interface/if_reset.d \
./Source/Interface/if_rotary.d \
./Source/Interface/if_serial_ae1.d \
./Source/Interface/if_serial_flash.d \
./Source/Interface/if_timer.d 


# Each subdirectory must supply rules for building sources it contributes
Source/Interface/%.o: ../Source/Interface/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


