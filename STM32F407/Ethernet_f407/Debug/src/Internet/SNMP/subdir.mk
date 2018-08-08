################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Internet/SNMP/snmp.c \
../src/Internet/SNMP/snmp_custom.c 

OBJS += \
./src/Internet/SNMP/snmp.o \
./src/Internet/SNMP/snmp_custom.o 

C_DEPS += \
./src/Internet/SNMP/snmp.d \
./src/Internet/SNMP/snmp_custom.d 


# Each subdirectory must supply rules for building sources it contributes
src/Internet/SNMP/%.o: ../src/Internet/SNMP/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -DDEBUG -I"../libs/misc/include" -I"../include" -I"../libs/cmsis/include" -I"../libs/StdPeriph/include" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


