################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/BlinkLed.c \
../src/HC-SR04.c \
../src/STM32F3_my.c \
../src/SystemInit.c \
../src/bitmap.c \
../src/bmp1.c \
../src/bmp4.c \
../src/common.c \
../src/graphics.c \
../src/lcd_drv.c \
../src/lcdlib.c \
../src/main.c \
../src/sensors.c \
../src/stm32303c_eval.c \
../src/stm32303c_eval_spi_sd.c \
../src/stm32f30x_it.c \
../src/stm32f3_discovery.c \
../src/stm32f3_discovery_l3gd20.c \
../src/stm32f3_discovery_lsm303dlhc.c 

OBJS += \
./src/BlinkLed.o \
./src/HC-SR04.o \
./src/STM32F3_my.o \
./src/SystemInit.o \
./src/bitmap.o \
./src/bmp1.o \
./src/bmp4.o \
./src/common.o \
./src/graphics.o \
./src/lcd_drv.o \
./src/lcdlib.o \
./src/main.o \
./src/sensors.o \
./src/stm32303c_eval.o \
./src/stm32303c_eval_spi_sd.o \
./src/stm32f30x_it.o \
./src/stm32f3_discovery.o \
./src/stm32f3_discovery_l3gd20.o \
./src/stm32f3_discovery_lsm303dlhc.o 

C_DEPS += \
./src/BlinkLed.d \
./src/HC-SR04.d \
./src/STM32F3_my.d \
./src/SystemInit.d \
./src/bitmap.d \
./src/bmp1.d \
./src/bmp4.d \
./src/common.d \
./src/graphics.d \
./src/lcd_drv.d \
./src/lcdlib.d \
./src/main.d \
./src/sensors.d \
./src/stm32303c_eval.d \
./src/stm32303c_eval_spi_sd.d \
./src/stm32f30x_it.d \
./src/stm32f3_discovery.d \
./src/stm32f3_discovery_l3gd20.d \
./src/stm32f3_discovery_lsm303dlhc.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -O1 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra  -g3 -gdwarf-2 -DOS_USE_TRACE_ITM -DSTM32F30X -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=72000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f3-stdperiph" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


