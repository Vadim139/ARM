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
../src/pwm.c \
../src/stm32f4_discovery.c \
../src/stm32f4_discovery_lis302dl.c \
../src/stm32f4xx_it.c \
../src/tm_stm32f4_adc.c \
../src/tm_stm32f4_gpio.c \
../src/tm_stm32f4_i2c.c \
../src/tm_stm32f4_spi.c \
../src/ts.c 

CPP_SRCS += \
../src/main.cpp 

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
./src/pwm.d \
./src/stm32f4_discovery.d \
./src/stm32f4_discovery_lis302dl.d \
./src/stm32f4xx_it.d \
./src/tm_stm32f4_adc.d \
./src/tm_stm32f4_gpio.d \
./src/tm_stm32f4_i2c.d \
./src/tm_stm32f4_spi.d \
./src/ts.d 

CPP_DEPS += \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DOS_USE_SEMIHOSTING -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/STM32F407" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DOS_USE_SEMIHOSTING -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/STM32F407" -std=gnu++11 -fabi-version=0 -fno-exceptions -fno-rtti -fno-use-cxa-atexit -fno-threadsafe-statics -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


