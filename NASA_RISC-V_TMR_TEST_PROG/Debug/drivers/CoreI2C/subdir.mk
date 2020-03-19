################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/CoreI2C/core_i2c.c \
../drivers/CoreI2C/i2c_interrupt.c 

OBJS += \
./drivers/CoreI2C/core_i2c.o \
./drivers/CoreI2C/i2c_interrupt.o 

C_DEPS += \
./drivers/CoreI2C/core_i2c.d \
./drivers/CoreI2C/i2c_interrupt.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/CoreI2C/%.o: ../drivers/CoreI2C/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv64-unknown-elf-gcc -march=rv32im -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:\Users\mashford\Documents\GitHub\PolarFire_RISC-V_TMR_SoftConsole\NASA_RISC-V_TMR_TEST_PROG\drivers\CoreGPIO" -I"C:\Users\mashford\Documents\GitHub\PolarFire_RISC-V_TMR_SoftConsole\NASA_RISC-V_TMR_TEST_PROG\drivers\CoreI2C" -I"C:\Users\mashford\Documents\GitHub\PolarFire_RISC-V_TMR_SoftConsole\NASA_RISC-V_TMR_TEST_PROG\drivers\CoreSPI" -I"C:\Users\mashford\Documents\GitHub\PolarFire_RISC-V_TMR_SoftConsole\NASA_RISC-V_TMR_TEST_PROG\drivers\CoreUARTapb" -I"C:\Users\mashford\Documents\GitHub\PolarFire_RISC-V_TMR_SoftConsole\NASA_RISC-V_TMR_TEST_PROG\hal" -I"C:\Users\mashford\Documents\GitHub\PolarFire_RISC-V_TMR_SoftConsole\NASA_RISC-V_TMR_TEST_PROG\riscv_hal" -I"C:\Users\mashford\Documents\GitHub\PolarFire_RISC-V_TMR_SoftConsole\NASA_RISC-V_TMR_TEST_PROG\drivers\CoreTimer" -I"C:\Users\mashford\Documents\GitHub\PolarFire_RISC-V_TMR_SoftConsole\NASA_RISC-V_TMR_TEST_PROG\i2c_test_files" -I"C:\Users\mashford\Documents\GitHub\PolarFire_RISC-V_TMR_SoftConsole\NASA_RISC-V_TMR_TEST_PROG\spi_test_files" -I"C:\Users\mashford\Documents\GitHub\PolarFire_RISC-V_TMR_SoftConsole\NASA_RISC-V_TMR_TEST_PROG\user_handler_files" -I"C:\Users\mashford\Documents\GitHub\PolarFire_RISC-V_TMR_SoftConsole\NASA_RISC-V_TMR_TEST_PROG\lcd_test_files" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


