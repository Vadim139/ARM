################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Ethernet/W5500/w5500.c 

OBJS += \
./src/Ethernet/W5500/w5500.o 

C_DEPS += \
./src/Ethernet/W5500/w5500.d 


# Each subdirectory must supply rules for building sources it contributes
src/Ethernet/W5500/%.o: ../src/Ethernet/W5500/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra  -g -DOS_USE_SEMIHOSTING1 -DRELEASE -DSTM32F40_41xxx -DOS_USE_TRACE_SEMIHOSTING_DEBUG1 -DSTM32F407xx -DUSE_HAL_DRIVER1 -DHSE_VALUE=8000000 -I"../include" -I"../system/include/stm32f4" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


