################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/BlinkLed.c \
../src/STM32F3_my.c \
../src/common.c \
../src/main.c \
../src/sensors.c \
../src/stm32f30x_it.c \
../src/stm32f3_discovery.c \
../src/stm32f3_discovery_l3gd20.c \
../src/stm32f3_discovery_lsm303dlhc.c 

OBJS += \
./src/BlinkLed.o \
./src/STM32F3_my.o \
./src/common.o \
./src/main.o \
./src/sensors.o \
./src/stm32f30x_it.o \
./src/stm32f3_discovery.o \
./src/stm32f3_discovery_l3gd20.o \
./src/stm32f3_discovery_lsm303dlhc.o 

C_DEPS += \
./src/BlinkLed.d \
./src/STM32F3_my.d \
./src/common.d \
./src/main.d \
./src/sensors.d \
./src/stm32f30x_it.d \
./src/stm32f3_discovery.d \
./src/stm32f3_discovery_l3gd20.d \
./src/stm32f3_discovery_lsm303dlhc.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_ITM -DSTM32F30X -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=72000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f3-stdperiph" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


