################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../system/src/stm32f1-stdperiph/misc.c \
../system/src/stm32f1-stdperiph/stm32f10x_adc.c \
../system/src/stm32f1-stdperiph/stm32f10x_bkp.c \
../system/src/stm32f1-stdperiph/stm32f10x_exti.c \
../system/src/stm32f1-stdperiph/stm32f10x_flash.c \
../system/src/stm32f1-stdperiph/stm32f10x_gpio.c \
../system/src/stm32f1-stdperiph/stm32f10x_i2c.c \
../system/src/stm32f1-stdperiph/stm32f10x_pwr.c \
../system/src/stm32f1-stdperiph/stm32f10x_rcc.c \
../system/src/stm32f1-stdperiph/stm32f10x_rtc.c \
../system/src/stm32f1-stdperiph/stm32f10x_spi.c \
../system/src/stm32f1-stdperiph/stm32f10x_tim.c \
../system/src/stm32f1-stdperiph/stm32f10x_usart.c 

OBJS += \
./system/src/stm32f1-stdperiph/misc.o \
./system/src/stm32f1-stdperiph/stm32f10x_adc.o \
./system/src/stm32f1-stdperiph/stm32f10x_bkp.o \
./system/src/stm32f1-stdperiph/stm32f10x_exti.o \
./system/src/stm32f1-stdperiph/stm32f10x_flash.o \
./system/src/stm32f1-stdperiph/stm32f10x_gpio.o \
./system/src/stm32f1-stdperiph/stm32f10x_i2c.o \
./system/src/stm32f1-stdperiph/stm32f10x_pwr.o \
./system/src/stm32f1-stdperiph/stm32f10x_rcc.o \
./system/src/stm32f1-stdperiph/stm32f10x_rtc.o \
./system/src/stm32f1-stdperiph/stm32f10x_spi.o \
./system/src/stm32f1-stdperiph/stm32f10x_tim.o \
./system/src/stm32f1-stdperiph/stm32f10x_usart.o 

C_DEPS += \
./system/src/stm32f1-stdperiph/misc.d \
./system/src/stm32f1-stdperiph/stm32f10x_adc.d \
./system/src/stm32f1-stdperiph/stm32f10x_bkp.d \
./system/src/stm32f1-stdperiph/stm32f10x_exti.d \
./system/src/stm32f1-stdperiph/stm32f10x_flash.d \
./system/src/stm32f1-stdperiph/stm32f10x_gpio.d \
./system/src/stm32f1-stdperiph/stm32f10x_i2c.d \
./system/src/stm32f1-stdperiph/stm32f10x_pwr.d \
./system/src/stm32f1-stdperiph/stm32f10x_rcc.d \
./system/src/stm32f1-stdperiph/stm32f10x_rtc.d \
./system/src/stm32f1-stdperiph/stm32f10x_spi.d \
./system/src/stm32f1-stdperiph/stm32f10x_tim.d \
./system/src/stm32f1-stdperiph/stm32f10x_usart.d 


# Each subdirectory must supply rules for building sources it contributes
system/src/stm32f1-stdperiph/%.o: ../system/src/stm32f1-stdperiph/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f1-stdperiph" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


