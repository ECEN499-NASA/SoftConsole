################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../spi_test_files/spi_test_prog.c 

OBJS += \
./spi_test_files/spi_test_prog.o 

C_DEPS += \
./spi_test_files/spi_test_prog.d 


# Each subdirectory must supply rules for building sources it contributes
spi_test_files/%.o: ../spi_test_files/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv64-unknown-elf-gcc -march=rv32im -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"D:\School\ECEN499\GitHub\SoftConsole\NASA_RISC-V_TMR_TEST_PROG\drivers\CoreGPIO" -I"D:\School\ECEN499\GitHub\SoftConsole\NASA_RISC-V_TMR_TEST_PROG\uart_test_files" -I"D:\School\ECEN499\GitHub\SoftConsole\NASA_RISC-V_TMR_TEST_PROG\drivers\CoreI2C" -I"D:\School\ECEN499\GitHub\SoftConsole\NASA_RISC-V_TMR_TEST_PROG\drivers\CoreSPI" -I"D:\School\ECEN499\GitHub\SoftConsole\NASA_RISC-V_TMR_TEST_PROG\drivers\CoreUARTapb" -I"D:\School\ECEN499\GitHub\SoftConsole\NASA_RISC-V_TMR_TEST_PROG\hal" -I"D:\School\ECEN499\GitHub\SoftConsole\NASA_RISC-V_TMR_TEST_PROG\riscv_hal" -I"D:\School\ECEN499\GitHub\SoftConsole\NASA_RISC-V_TMR_TEST_PROG\drivers\CoreTimer" -I"D:\School\ECEN499\GitHub\SoftConsole\NASA_RISC-V_TMR_TEST_PROG\i2c_test_files" -I"D:\School\ECEN499\GitHub\SoftConsole\NASA_RISC-V_TMR_TEST_PROG\spi_test_files" -I"D:\School\ECEN499\GitHub\SoftConsole\NASA_RISC-V_TMR_TEST_PROG\user_handler_files" -I"D:\School\ECEN499\GitHub\SoftConsole\NASA_RISC-V_TMR_TEST_PROG\lcd_test_files" -include"D:\School\ECEN499\GitHub\SoftConsole\NASA_RISC-V_TMR_TEST_PROG\uart_test_files\uart_test_routine.h" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


