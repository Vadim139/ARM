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
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DSTM32F429_439xx -D__cplusplus1 -DUSE_FULL_ASSERT1 -DOS_USE_SEMIHOSTING -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DUSE_HAL_DRIVER_NO -DHSE_VALUE=16000000 -I"../include" -I"../src" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


