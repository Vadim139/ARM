################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/STM32F3_my.c \
../src/_write.c \
../src/common.c \
../src/functions.c \
../src/pwm.c \
../src/stm32f4_discovery.c \
../src/stm32f4xx_it.c \
../src/tm_stm32f4_adc.c \
../src/tm_stm32f4_gpio.c \
../src/tm_stm32f4_i2c.c \
../src/tm_stm32f4_mco_output.c \
../src/tm_stm32f4_spi.c 

CPP_SRCS += \
../src/STM32F4_Class.cpp \
../src/STM32F4_my.cpp \
../src/Sensor.cpp \
../src/Timer.cpp \
../src/main.cpp 

OBJS += \
./src/STM32F3_my.o \
./src/STM32F4_Class.o \
./src/STM32F4_my.o \
./src/Sensor.o \
./src/Timer.o \
./src/_write.o \
./src/common.o \
./src/functions.o \
./src/main.o \
./src/pwm.o \
./src/stm32f4_discovery.o \
./src/stm32f4xx_it.o \
./src/tm_stm32f4_adc.o \
./src/tm_stm32f4_gpio.o \
./src/tm_stm32f4_i2c.o \
./src/tm_stm32f4_mco_output.o \
./src/tm_stm32f4_spi.o 

C_DEPS += \
./src/STM32F3_my.d \
./src/_write.d \
./src/common.d \
./src/functions.d \
./src/pwm.d \
./src/stm32f4_discovery.d \
./src/stm32f4xx_it.d \
./src/tm_stm32f4_adc.d \
./src/tm_stm32f4_gpio.d \
./src/tm_stm32f4_i2c.d \
./src/tm_stm32f4_mco_output.d \
./src/tm_stm32f4_spi.d 

CPP_DEPS += \
./src/STM32F4_Class.d \
./src/STM32F4_my.d \
./src/Sensor.d \
./src/Timer.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DOS_USE_SEMIHOSTING -DUSE_STDPERIPH_DRIVER -DSTM32F40_41xxx -DUSE_FULL_ASSERT1 -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F407xx -DUSE_HAL_DRIVER_NO -DHSE_VALUE=8000000 -I"../include" -I"../system/include/stm32f4-hal" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DOS_USE_SEMIHOSTING -DUSE_STDPERIPH_DRIVER -DSTM32F40_41xxx -DUSE_FULL_ASSERT1 -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F407xx -DUSE_HAL_DRIVER_NO -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4" -I"../system/include/stm32f4-hal" -std=gnu++11 -fabi-version=0 -fno-exceptions -fno-rtti -fno-use-cxa-atexit -fno-threadsafe-statics -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


