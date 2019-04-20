################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../system/src/stm32f4/misc.c \
../system/src/stm32f4/stm32f4xx_adc.c \
../system/src/stm32f4/stm32f4xx_exti.c \
../system/src/stm32f4/stm32f4xx_gpio.c \
../system/src/stm32f4/stm32f4xx_i2c.c \
../system/src/stm32f4/stm32f4xx_rcc.c \
../system/src/stm32f4/stm32f4xx_rtc.c \
../system/src/stm32f4/stm32f4xx_spi.c \
../system/src/stm32f4/stm32f4xx_syscfg.c \
../system/src/stm32f4/stm32f4xx_tim.c \
../system/src/stm32f4/stm32f4xx_usart.c 

OBJS += \
./system/src/stm32f4/misc.o \
./system/src/stm32f4/stm32f4xx_adc.o \
./system/src/stm32f4/stm32f4xx_exti.o \
./system/src/stm32f4/stm32f4xx_gpio.o \
./system/src/stm32f4/stm32f4xx_i2c.o \
./system/src/stm32f4/stm32f4xx_rcc.o \
./system/src/stm32f4/stm32f4xx_rtc.o \
./system/src/stm32f4/stm32f4xx_spi.o \
./system/src/stm32f4/stm32f4xx_syscfg.o \
./system/src/stm32f4/stm32f4xx_tim.o \
./system/src/stm32f4/stm32f4xx_usart.o 

C_DEPS += \
./system/src/stm32f4/misc.d \
./system/src/stm32f4/stm32f4xx_adc.d \
./system/src/stm32f4/stm32f4xx_exti.d \
./system/src/stm32f4/stm32f4xx_gpio.d \
./system/src/stm32f4/stm32f4xx_i2c.d \
./system/src/stm32f4/stm32f4xx_rcc.d \
./system/src/stm32f4/stm32f4xx_rtc.d \
./system/src/stm32f4/stm32f4xx_spi.d \
./system/src/stm32f4/stm32f4xx_syscfg.d \
./system/src/stm32f4/stm32f4xx_tim.d \
./system/src/stm32f4/stm32f4xx_usart.d 


# Each subdirectory must supply rules for building sources it contributes
system/src/stm32f4/%.o: ../system/src/stm32f4/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DOS_USE_SEMIHOSTING -DUSE_STDPERIPH_DRIVER -DSTM32F40_41xxx -DUSE_FULL_ASSERT1 -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F407xx -DUSE_HAL_DRIVER_NO -DHSE_VALUE=8000000 -I"../include" -I"../system/include/stm32f4-hal" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


