################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../system/src/stm32f3-stdperiph/stm32f30x_adc.c \
../system/src/stm32f3-stdperiph/stm32f30x_can.c \
../system/src/stm32f3-stdperiph/stm32f30x_comp.c \
../system/src/stm32f3-stdperiph/stm32f30x_crc.c \
../system/src/stm32f3-stdperiph/stm32f30x_dac.c \
../system/src/stm32f3-stdperiph/stm32f30x_dbgmcu.c \
../system/src/stm32f3-stdperiph/stm32f30x_dma.c \
../system/src/stm32f3-stdperiph/stm32f30x_exti.c \
../system/src/stm32f3-stdperiph/stm32f30x_flash.c \
../system/src/stm32f3-stdperiph/stm32f30x_gpio.c \
../system/src/stm32f3-stdperiph/stm32f30x_i2c.c \
../system/src/stm32f3-stdperiph/stm32f30x_iwdg.c \
../system/src/stm32f3-stdperiph/stm32f30x_misc.c \
../system/src/stm32f3-stdperiph/stm32f30x_opamp.c \
../system/src/stm32f3-stdperiph/stm32f30x_pwr.c \
../system/src/stm32f3-stdperiph/stm32f30x_rcc.c \
../system/src/stm32f3-stdperiph/stm32f30x_rtc.c \
../system/src/stm32f3-stdperiph/stm32f30x_spi.c \
../system/src/stm32f3-stdperiph/stm32f30x_syscfg.c \
../system/src/stm32f3-stdperiph/stm32f30x_tim.c \
../system/src/stm32f3-stdperiph/stm32f30x_usart.c \
../system/src/stm32f3-stdperiph/stm32f30x_wwdg.c 

OBJS += \
./system/src/stm32f3-stdperiph/stm32f30x_adc.o \
./system/src/stm32f3-stdperiph/stm32f30x_can.o \
./system/src/stm32f3-stdperiph/stm32f30x_comp.o \
./system/src/stm32f3-stdperiph/stm32f30x_crc.o \
./system/src/stm32f3-stdperiph/stm32f30x_dac.o \
./system/src/stm32f3-stdperiph/stm32f30x_dbgmcu.o \
./system/src/stm32f3-stdperiph/stm32f30x_dma.o \
./system/src/stm32f3-stdperiph/stm32f30x_exti.o \
./system/src/stm32f3-stdperiph/stm32f30x_flash.o \
./system/src/stm32f3-stdperiph/stm32f30x_gpio.o \
./system/src/stm32f3-stdperiph/stm32f30x_i2c.o \
./system/src/stm32f3-stdperiph/stm32f30x_iwdg.o \
./system/src/stm32f3-stdperiph/stm32f30x_misc.o \
./system/src/stm32f3-stdperiph/stm32f30x_opamp.o \
./system/src/stm32f3-stdperiph/stm32f30x_pwr.o \
./system/src/stm32f3-stdperiph/stm32f30x_rcc.o \
./system/src/stm32f3-stdperiph/stm32f30x_rtc.o \
./system/src/stm32f3-stdperiph/stm32f30x_spi.o \
./system/src/stm32f3-stdperiph/stm32f30x_syscfg.o \
./system/src/stm32f3-stdperiph/stm32f30x_tim.o \
./system/src/stm32f3-stdperiph/stm32f30x_usart.o \
./system/src/stm32f3-stdperiph/stm32f30x_wwdg.o 

C_DEPS += \
./system/src/stm32f3-stdperiph/stm32f30x_adc.d \
./system/src/stm32f3-stdperiph/stm32f30x_can.d \
./system/src/stm32f3-stdperiph/stm32f30x_comp.d \
./system/src/stm32f3-stdperiph/stm32f30x_crc.d \
./system/src/stm32f3-stdperiph/stm32f30x_dac.d \
./system/src/stm32f3-stdperiph/stm32f30x_dbgmcu.d \
./system/src/stm32f3-stdperiph/stm32f30x_dma.d \
./system/src/stm32f3-stdperiph/stm32f30x_exti.d \
./system/src/stm32f3-stdperiph/stm32f30x_flash.d \
./system/src/stm32f3-stdperiph/stm32f30x_gpio.d \
./system/src/stm32f3-stdperiph/stm32f30x_i2c.d \
./system/src/stm32f3-stdperiph/stm32f30x_iwdg.d \
./system/src/stm32f3-stdperiph/stm32f30x_misc.d \
./system/src/stm32f3-stdperiph/stm32f30x_opamp.d \
./system/src/stm32f3-stdperiph/stm32f30x_pwr.d \
./system/src/stm32f3-stdperiph/stm32f30x_rcc.d \
./system/src/stm32f3-stdperiph/stm32f30x_rtc.d \
./system/src/stm32f3-stdperiph/stm32f30x_spi.d \
./system/src/stm32f3-stdperiph/stm32f30x_syscfg.d \
./system/src/stm32f3-stdperiph/stm32f30x_tim.d \
./system/src/stm32f3-stdperiph/stm32f30x_usart.d \
./system/src/stm32f3-stdperiph/stm32f30x_wwdg.d 


# Each subdirectory must supply rules for building sources it contributes
system/src/stm32f3-stdperiph/%.o: ../system/src/stm32f3-stdperiph/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -O1 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra  -g3 -gdwarf-2 -DOS_USE_TRACE_ITM -DSTM32F30X -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=72000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f3-stdperiph" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


