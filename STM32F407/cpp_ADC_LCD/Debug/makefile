################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/Internet/DNS/subdir.mk
-include src/Internet/DHCP/subdir.mk
-include src/Ethernet/W5500/subdir.mk
-include src/Ethernet/subdir.mk
-include src/subdir.mk
-include libs/misc/src/subdir.mk
-include libs/cmsis/src/subdir.mk
-include libs/StdPeriph/src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
cpp_ADC_LCD.hex \

SECONDARY_SIZE += \
cpp_ADC_LCD.siz \


# All Target
all: cpp_ADC_LCD.elf secondary-outputs

# Tool invocations
cpp_ADC_LCD.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross ARM C Linker'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -T libs.ld -T mem.ld -T sections.ld -nostartfiles -Xlinker --gc-sections -L"../ldscripts" -Wl,-Map,"cpp_ADC_LCD.map" -o "cpp_ADC_LCD.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

cpp_ADC_LCD.hex: cpp_ADC_LCD.elf
	@echo 'Invoking: Cross ARM GNU Create Flash Image'
	arm-none-eabi-objcopy -O ihex "cpp_ADC_LCD.elf"  "cpp_ADC_LCD.hex"
	@echo 'Finished building: $@'
	@echo ' '

cpp_ADC_LCD.siz: cpp_ADC_LCD.elf
	@echo 'Invoking: Cross ARM GNU Print Size'
	arm-none-eabi-size --format=berkeley "cpp_ADC_LCD.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(SECONDARY_FLASH)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS) cpp_ADC_LCD.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
