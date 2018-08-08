################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/OV7670_I2C.c \
../src/PCF8583.c \
../src/STM32F3_my.c \
../src/clock-arch.c \
../src/common.c \
../src/enc424j600.c \
../src/lcd_drv.c \
../src/lcdlib.c \
../src/main.c \
../src/network.c \
../src/psock.c \
../src/simple-httpd.c \
../src/stm32f4_discovery.c \
../src/stm32f4_discovery_audio_codec.c \
../src/stm32f4_discovery_lis302dl.c \
../src/stm32f4xx_it.c \
../src/timer.c \
../src/tm_stm32f4_gpio.c \
../src/tm_stm32f4_i2c.c \
../src/tm_stm32f4_spi.c \
../src/uip-fw.c \
../src/uip-neighbor.c \
../src/uip-split.c \
../src/uip.c \
../src/uip_arp.c \
../src/uiplib.c 

OBJS += \
./src/OV7670_I2C.o \
./src/PCF8583.o \
./src/STM32F3_my.o \
./src/clock-arch.o \
./src/common.o \
./src/enc424j600.o \
./src/lcd_drv.o \
./src/lcdlib.o \
./src/main.o \
./src/network.o \
./src/psock.o \
./src/simple-httpd.o \
./src/stm32f4_discovery.o \
./src/stm32f4_discovery_audio_codec.o \
./src/stm32f4_discovery_lis302dl.o \
./src/stm32f4xx_it.o \
./src/timer.o \
./src/tm_stm32f4_gpio.o \
./src/tm_stm32f4_i2c.o \
./src/tm_stm32f4_spi.o \
./src/uip-fw.o \
./src/uip-neighbor.o \
./src/uip-split.o \
./src/uip.o \
./src/uip_arp.o \
./src/uiplib.o 

C_DEPS += \
./src/OV7670_I2C.d \
./src/PCF8583.d \
./src/STM32F3_my.d \
./src/clock-arch.d \
./src/common.d \
./src/enc424j600.d \
./src/lcd_drv.d \
./src/lcdlib.d \
./src/main.d \
./src/network.d \
./src/psock.d \
./src/simple-httpd.d \
./src/stm32f4_discovery.d \
./src/stm32f4_discovery_audio_codec.d \
./src/stm32f4_discovery_lis302dl.d \
./src/stm32f4xx_it.d \
./src/timer.d \
./src/tm_stm32f4_gpio.d \
./src/tm_stm32f4_i2c.d \
./src/tm_stm32f4_spi.d \
./src/uip-fw.d \
./src/uip-neighbor.d \
./src/uip-split.d \
./src/uip.d \
./src/uip_arp.d \
./src/uiplib.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -DDEBUG -I"../libs/misc/include" -I"../include" -I"../libs/cmsis/include" -I"../libs/StdPeriph/include" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


