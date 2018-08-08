################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/CT_I2C.c \
../src/Delay.c \
../src/GT811.c \
../src/LCD_Interface.c \
../src/RA8875_Driver.c \
../src/STM32F3_my.c \
../src/camera_api.c \
../src/common.c \
../src/dcmi_ov2640.c \
../src/stm32f4xx_it.c \
../src/tm_stm32f4_gpio.c \
../src/tree.c 

CPP_SRCS += \
../src/STM32F4_Class.cpp \
../src/main.cpp 

OBJS += \
./src/CT_I2C.o \
./src/Delay.o \
./src/GT811.o \
./src/LCD_Interface.o \
./src/RA8875_Driver.o \
./src/STM32F3_my.o \
./src/STM32F4_Class.o \
./src/camera_api.o \
./src/common.o \
./src/dcmi_ov2640.o \
./src/main.o \
./src/stm32f4xx_it.o \
./src/tm_stm32f4_gpio.o \
./src/tree.o 

C_DEPS += \
./src/CT_I2C.d \
./src/Delay.d \
./src/GT811.d \
./src/LCD_Interface.d \
./src/RA8875_Driver.d \
./src/STM32F3_my.d \
./src/camera_api.d \
./src/common.d \
./src/dcmi_ov2640.d \
./src/stm32f4xx_it.d \
./src/tm_stm32f4_gpio.d \
./src/tree.d 

CPP_DEPS += \
./src/STM32F4_Class.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DARM_MATH_CM4 -DSTM32F429_439xx -D__cplusplus1 -DUSE_FULL_ASSERT1 -DOS_USE_SEMIHOSTING -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DUSE_HAL_DRIVER_NO -DHSE_VALUE=16000000 -I"../include" -I"../src" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DSTM32F429_439xx -D__cplusplus1 -DUSE_FULL_ASSERT1 -DOS_USE_SEMIHOSTING -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DUSE_HAL_DRIVER_NO -DHSE_VALUE=16000000 -I"../include" -I"../src" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4" -std=gnu++11 -fabi-version=0 -fno-exceptions -fno-rtti -fno-use-cxa-atexit -fno-threadsafe-statics -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


