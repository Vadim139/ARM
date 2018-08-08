################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Ethernet/socket.c \
../src/Ethernet/wizchip_conf.c 

OBJS += \
./src/Ethernet/socket.o \
./src/Ethernet/wizchip_conf.o 

C_DEPS += \
./src/Ethernet/socket.d \
./src/Ethernet/wizchip_conf.d 


# Each subdirectory must supply rules for building sources it contributes
src/Ethernet/%.o: ../src/Ethernet/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra  -g -DOS_USE_SEMIHOSTING -DRELEASE -DSTM32F40_41xxx -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F407xx -DUSE_HAL_DRIVER1 -DHSE_VALUE=8000000 -I"../include" -I"../system/include/stm32f4" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


