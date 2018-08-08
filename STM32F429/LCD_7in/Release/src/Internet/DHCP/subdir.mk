################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Internet/DHCP/dhcp.c 

OBJS += \
./src/Internet/DHCP/dhcp.o 

C_DEPS += \
./src/Internet/DHCP/dhcp.d 


# Each subdirectory must supply rules for building sources it contributes
src/Internet/DHCP/%.o: ../src/Internet/DHCP/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra  -g -DOS_USE_SEMIHOSTING -DRELEASE -DSTM32F40_41xxx -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F407xx -DUSE_HAL_DRIVER1 -DHSE_VALUE=8000000 -I"../include" -I"../system/include/stm32f4" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


