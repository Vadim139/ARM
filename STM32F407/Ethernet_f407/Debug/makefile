################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/PlatformHandler/subdir.mk
-include src/Internet/httpServer/subdir.mk
-include src/Internet/TFTP/subdir.mk
-include src/Internet/SNTP/subdir.mk
-include src/Internet/SNMP/subdir.mk
-include src/Internet/FTPServer/subdir.mk
-include src/Internet/FTPClient/subdir.mk
-include src/Internet/DNS/subdir.mk
-include src/Internet/DHCP/subdir.mk
-include src/Ethernet/W5500/subdir.mk
-include src/Ethernet/W5300/subdir.mk
-include src/Ethernet/W5200/subdir.mk
-include src/Ethernet/W5100/subdir.mk
-include src/Ethernet/subdir.mk
-include src/Application/loopback/subdir.mk
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
Ethernet_f407.hex \

SECONDARY_SIZE += \
Ethernet_f407.siz \


# All Target
all: Ethernet_f407.elf secondary-outputs

# Tool invocations
Ethernet_f407.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross ARM C Linker'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -T libs.ld -T mem.ld -T sections.ld -nostartfiles -Xlinker --gc-sections -L"../ldscripts" -Wl,-Map,"Ethernet_f407.map" -o "Ethernet_f407.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Ethernet_f407.hex: Ethernet_f407.elf
	@echo 'Invoking: Cross ARM GNU Create Flash Image'
	arm-none-eabi-objcopy -O ihex "Ethernet_f407.elf"  "Ethernet_f407.hex"
	@echo 'Finished building: $@'
	@echo ' '

Ethernet_f407.siz: Ethernet_f407.elf
	@echo 'Invoking: Cross ARM GNU Print Size'
	arm-none-eabi-size --format=berkeley "Ethernet_f407.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(SECONDARY_FLASH)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS) Ethernet_f407.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
