################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/LCD_STM32F4.c \
../src/OV7670_I2C.c \
../src/SCCB.c \
../src/STM32F3_my.c \
../src/common.c \
../src/fonts.c \
../src/functions.c \
../src/pwm.c \
../src/stm32f4_discovery.c \
../src/stm32f4_discovery_lis302dl.c \
../src/stm32f4xx_it.c \
../src/tm_stm32f4_adc.c \
../src/tm_stm32f4_gpio.c \
../src/tm_stm32f4_i2c.c \
../src/tm_stm32f4_mco_output.c \
../src/tm_stm32f4_spi.c \
../src/ts.c 

CPP_SRCS += \
../src/STM32F4_Class.cpp \
../src/STM32F4_my.cpp \
../src/main.cpp 

OBJS += \
./src/LCD_STM32F4.o \
./src/OV7670_I2C.o \
./src/SCCB.o \
./src/STM32F3_my.o \
./src/STM32F4_Class.o \
./src/STM32F4_my.o \
./src/common.o \
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
./src/tm_stm32f4_mco_output.o \
./src/tm_stm32f4_spi.o \
./src/ts.o 

C_DEPS += \
./src/LCD_STM32F4.d \
./src/OV7670_I2C.d \
./src/SCCB.d \
./src/STM32F3_my.d \
./src/common.d \
./src/fonts.d \
./src/functions.d \
./src/pwm.d \
./src/stm32f4_discovery.d \
./src/stm32f4_discovery_lis302dl.d \
./src/stm32f4xx_it.d \
./src/tm_stm32f4_adc.d \
./src/tm_stm32f4_gpio.d \
./src/tm_stm32f4_i2c.d \
./src/tm_stm32f4_mco_output.d \
./src/tm_stm32f4_spi.d \
./src/ts.d 

CPP_DEPS += \
./src/STM32F4_Class.d \
./src/STM32F4_my.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DSTM32F429_439xx -D__cplusplus1 -DUSE_FULL_ASSERT1 -DOS_USE_SEMIHOSTING -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DUSE_HAL_DRIVER_NO -DHSE_VALUE=16000000 -I"../include" -I"../src" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DSTM32F429_439xx -D__cplusplus1 -DUSE_FULL_ASSERT1 -DOS_USE_SEMIHOSTING -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DUSE_HAL_DRIVER_NO -DHSE_VALUE=16000000 -I"../include" -I"../src" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4" -std=gnu++11 -fabi-version=0 -fno-exceptions -fno-rtti -fno-use-cxa-atexit -fno-threadsafe-statics -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


