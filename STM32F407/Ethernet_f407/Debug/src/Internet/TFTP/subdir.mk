################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Internet/TFTP/netutil.c \
../src/Internet/TFTP/tftp.c 

OBJS += \
./src/Internet/TFTP/netutil.o \
./src/Internet/TFTP/tftp.o 

C_DEPS += \
./src/Internet/TFTP/netutil.d \
./src/Internet/TFTP/tftp.d 


# Each subdirectory must supply rules for building sources it contributes
src/Internet/TFTP/%.o: ../src/Internet/TFTP/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -DDEBUG -I"../libs/misc/include" -I"../include" -I"../libs/cmsis/include" -I"../libs/StdPeriph/include" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


