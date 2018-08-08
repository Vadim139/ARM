################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/_write.c \
../src/buffer.c \
../src/stm32f1xx_it.c 

CPP_SRCS += \
../src/ADC.cpp \
../src/Atmega.cpp \
../src/BlinkLed.cpp \
../src/DataBase.cpp \
../src/EE_memory.cpp \
../src/ESP8266.cpp \
../src/NET.cpp \
../src/NTC.cpp \
../src/Other.cpp \
../src/RS485.cpp \
../src/RTC.cpp \
../src/SIM800L.cpp \
../src/STM32F4_Class.cpp \
../src/Timer.cpp \
../src/main.cpp \
../src/md5.cpp 

OBJS += \
./src/ADC.o \
./src/Atmega.o \
./src/BlinkLed.o \
./src/DataBase.o \
./src/EE_memory.o \
./src/ESP8266.o \
./src/NET.o \
./src/NTC.o \
./src/Other.o \
./src/RS485.o \
./src/RTC.o \
./src/SIM800L.o \
./src/STM32F4_Class.o \
./src/Timer.o \
./src/_write.o \
./src/buffer.o \
./src/main.o \
./src/md5.o \
./src/stm32f1xx_it.o 

C_DEPS += \
./src/_write.d \
./src/buffer.d \
./src/stm32f1xx_it.d 

CPP_DEPS += \
./src/ADC.d \
./src/Atmega.d \
./src/BlinkLed.d \
./src/DataBase.d \
./src/EE_memory.d \
./src/ESP8266.d \
./src/NET.d \
./src/NTC.d \
./src/Other.d \
./src/RS485.d \
./src/RTC.d \
./src/SIM800L.d \
./src/STM32F4_Class.d \
./src/Timer.d \
./src/main.d \
./src/md5.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f1-stdperiph" -std=gnu++11 -fabi-version=0 -fno-exceptions -fno-rtti -fno-use-cxa-atexit -fno-threadsafe-statics -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f1-stdperiph" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


