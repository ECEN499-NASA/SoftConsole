################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../i2c_test_files/i2c_test_routine.c 

OBJS += \
./i2c_test_files/i2c_test_routine.o 

C_DEPS += \
./i2c_test_files/i2c_test_routine.d 


# Each subdirectory must supply rules for building sources it contributes
i2c_test_files/%.o: ../i2c_test_files/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv64-unknown-elf-gcc -march=rv32im -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:\ECEN499-TeamE\SoftConsole\SoftConsole\NASA_RISC-V_TMR_TEST_PROG\drivers\CoreGPIO" -I"C:\ECEN499-TeamE\SoftConsole\SoftConsole\NASA_RISC-V_TMR_TEST_PROG\uart_test_files" -I"C:\ECEN499-TeamE\SoftConsole\SoftConsole\NASA_RISC-V_TMR_TEST_PROG\drivers\CoreI2C" -I"C:\ECEN499-TeamE\SoftConsole\SoftConsole\NASA_RISC-V_TMR_TEST_PROG\drivers\CoreSPI" -I"C:\ECEN499-TeamE\SoftConsole\SoftConsole\NASA_RISC-V_TMR_TEST_PROG\drivers\CoreUARTapb" -I"C:\ECEN499-TeamE\SoftConsole\SoftConsole\NASA_RISC-V_TMR_TEST_PROG\hal" -I"C:\ECEN499-TeamE\SoftConsole\SoftConsole\NASA_RISC-V_TMR_TEST_PROG\riscv_hal" -I"C:\ECEN499-TeamE\SoftConsole\SoftConsole\NASA_RISC-V_TMR_TEST_PROG\drivers\CoreTimer" -I"C:\ECEN499-TeamE\SoftConsole\SoftConsole\NASA_RISC-V_TMR_TEST_PROG\i2c_test_files" -I"C:\ECEN499-TeamE\SoftConsole\SoftConsole\NASA_RISC-V_TMR_TEST_PROG\GPIO_test_files" -I"C:\ECEN499-TeamE\SoftConsole\SoftConsole\NASA_RISC-V_TMR_TEST_PROG\spi_test_files" -I"C:\ECEN499-TeamE\SoftConsole\SoftConsole\NASA_RISC-V_TMR_TEST_PROG\user_handler_files" -I"C:\ECEN499-TeamE\SoftConsole\SoftConsole\NASA_RISC-V_TMR_TEST_PROG\lcd_test_files" -include"C:\ECEN499-TeamE\SoftConsole\SoftConsole\NASA_RISC-V_TMR_TEST_PROG\uart_test_files\uart_test_routine.h" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


