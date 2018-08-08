################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/LCD_STM32F4.c \
../src/OV7670_I2C.c \
../src/STM32F3_my.c \
../src/_initialize_hardware.c \
../src/_write.c \
../src/common.c \
../src/fonts.c \
../src/functions.c \
../src/stm32f4xx_hal_msp.c \
../src/stm32f4xx_it.c \
../src/tm_stm32_adc.c \
../src/tm_stm32_exti.c \
../src/tm_stm32_gpio.c \
../src/tm_stm32_i2c.c \
../src/tm_stm32_spi.c 

CPP_SRCS += \
../src/BlinkLed.cpp \
../src/STM32F4_Class.cpp \
../src/STM32F4_my.cpp \
../src/Timer.cpp \
../src/main.cpp 

OBJS += \
./src/BlinkLed.o \
./src/LCD_STM32F4.o \
./src/OV7670_I2C.o \
./src/STM32F3_my.o \
./src/STM32F4_Class.o \
./src/STM32F4_my.o \
./src/Timer.o \
./src/_initialize_hardware.o \
./src/_write.o \
./src/common.o \
./src/fonts.o \
./src/functions.o \
./src/main.o \
./src/stm32f4xx_hal_msp.o \
./src/stm32f4xx_it.o \
./src/tm_stm32_adc.o \
./src/tm_stm32_exti.o \
./src/tm_stm32_gpio.o \
./src/tm_stm32_i2c.o \
./src/tm_stm32_spi.o 

C_DEPS += \
./src/LCD_STM32F4.d \
./src/OV7670_I2C.d \
./src/STM32F3_my.d \
./src/_initialize_hardware.d \
./src/_write.d \
./src/common.d \
./src/fonts.d \
./src/functions.d \
./src/stm32f4xx_hal_msp.d \
./src/stm32f4xx_it.d \
./src/tm_stm32_adc.d \
./src/tm_stm32_exti.d \
./src/tm_stm32_gpio.d \
./src/tm_stm32_i2c.d \
./src/tm_stm32_spi.d 

CPP_DEPS += \
./src/BlinkLed.d \
./src/STM32F4_Class.d \
./src/STM32F4_my.d \
./src/Timer.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DOS_USE_SEMIHOSTING -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F429xx -DUSE_HAL_DRIVER -DHSE_VALUE=16000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -std=gnu++11 -fabi-version=0 -fno-exceptions -fno-rtti -fno-use-cxa-atexit -fno-threadsafe-statics -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DOS_USE_SEMIHOSTING -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F429xx -DUSE_HAL_DRIVER -DHSE_VALUE=16000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/stm32f4xx_hal_msp.o: ../src/stm32f4xx_hal_msp.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DOS_USE_SEMIHOSTING -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F429xx -DUSE_HAL_DRIVER -DHSE_VALUE=16000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -std=gnu11 -Wno-missing-prototypes -Wno-missing-declarations -MMD -MP -MF"$(@:%.o=%.d)" -MT"src/stm32f4xx_hal_msp.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


