################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/LCD_STM32F4.c \
../src/OV7670_I2C.c \
../src/STM32F3_my.c \
../src/fonts.c \
../src/functions.c \
../src/main.c \
../src/pwm.c \
../src/stm32f4_discovery.c \
../src/stm32f4_discovery_lis302dl.c \
../src/stm32f4xx_it.c \
../src/tm_stm32f4_adc.c \
../src/tm_stm32f4_gpio.c \
../src/tm_stm32f4_i2c.c \
../src/tm_stm32f4_spi.c \
../src/ts.c 

OBJS += \
./src/LCD_STM32F4.o \
./src/OV7670_I2C.o \
./src/STM32F3_my.o \
./src/fonts.o \
./src/functions.o \
./src/main.o \
./src/pwm.o \
./src/stm32f4_discovery.o \
./src/stm32f4_discovery_lis302dl.o \
./src/stm32f4xx_it.o \
./src/tm_stm32f4_adc.o \
./src/tm_stm32f4_gpio.o \
./src/tm_stm32f4_i2c.o \
./src/tm_stm32f4_spi.o \
./src/ts.o 

C_DEPS += \
./src/LCD_STM32F4.d \
./src/OV7670_I2C.d \
./src/STM32F3_my.d \
./src/fonts.d \
./src/functions.d \
./src/main.d \
./src/pwm.d \
./src/stm32f4_discovery.d \
./src/stm32f4_discovery_lis302dl.d \
./src/stm32f4xx_it.d \
./src/tm_stm32f4_adc.d \
./src/tm_stm32f4_gpio.d \
./src/tm_stm32f4_i2c.d \
./src/tm_stm32f4_spi.d \
./src/ts.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -DDEBUG -I"../libs/misc/include" -I"../include" -I"../libs/cmsis/include" -I"../libs/StdPeriph/include" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


