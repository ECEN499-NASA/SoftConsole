################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include user_handler_files/subdir.mk
-include spi_test_files/subdir.mk
-include riscv_hal/subdir.mk
-include i2c_test_files/subdir.mk
-include hal/subdir.mk
-include drivers/CoreUARTapb/subdir.mk
-include drivers/CoreTimer/subdir.mk
-include drivers/CoreSPI/subdir.mk
-include drivers/CoreI2C/subdir.mk
-include drivers/CoreGPIO/subdir.mk
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
NASA_RISC-V_TMR_TEST_PROG.hex \

SECONDARY_SIZE += \
NASA_RISC-V_TMR_TEST_PROG.siz \


# All Target
all: NASA_RISC-V_TMR_TEST_PROG.elf secondary-outputs

# Tool invocations
NASA_RISC-V_TMR_TEST_PROG.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU RISC-V Cross C Linker'
	riscv64-unknown-elf-gcc -march=rv32im -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -T "C:\Users\Public\Documents\Libero\SoftConsole_Code\NASA_RISC-V_TMR_TEST_PROG\riscv_hal\microsemi-riscv-ram.ld" -nostartfiles -Xlinker --gc-sections -Wl,-Map,"NASA_RISC-V_TMR_TEST_PROG.map" -o "NASA_RISC-V_TMR_TEST_PROG.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

NASA_RISC-V_TMR_TEST_PROG.hex: NASA_RISC-V_TMR_TEST_PROG.elf
	@echo 'Invoking: GNU RISC-V Cross Create Flash Image'
	riscv64-unknown-elf-objcopy -O ihex --change-section-lma *-0x80000000 "NASA_RISC-V_TMR_TEST_PROG.elf"  "NASA_RISC-V_TMR_TEST_PROG.hex"
	@echo 'Finished building: $@'
	@echo ' '

NASA_RISC-V_TMR_TEST_PROG.siz: NASA_RISC-V_TMR_TEST_PROG.elf
	@echo 'Invoking: GNU RISC-V Cross Print Size'
	riscv64-unknown-elf-size --format=berkeley "NASA_RISC-V_TMR_TEST_PROG.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(SECONDARY_FLASH)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS) NASA_RISC-V_TMR_TEST_PROG.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
