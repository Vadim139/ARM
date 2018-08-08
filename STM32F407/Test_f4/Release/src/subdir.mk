################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/STM32F3_my.c \
../src/Timer.c \
../src/main.c \
../src/stm32f4_discovery.c \
../src/stm32f4_discovery_audio_codec.c \
../src/stm32f4_discovery_lis302dl.c \
../src/stm32f4xx_it.c \
../src/system_stm32f4xx.c 

OBJS += \
./src/STM32F3_my.o \
./src/Timer.o \
./src/main.o \
./src/stm32f4_discovery.o \
./src/stm32f4_discovery_audio_codec.o \
./src/stm32f4_discovery_lis302dl.o \
./src/stm32f4xx_it.o \
./src/system_stm32f4xx.o 

C_DEPS += \
./src/STM32F3_my.d \
./src/Timer.d \
./src/main.d \
./src/stm32f4_discovery.d \
./src/stm32f4_discovery_audio_codec.d \
./src/stm32f4_discovery_lis302dl.d \
./src/stm32f4xx_it.d \
./src/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra  -g -DOS_USE_TRACE_ITM -DSTM32F407xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


