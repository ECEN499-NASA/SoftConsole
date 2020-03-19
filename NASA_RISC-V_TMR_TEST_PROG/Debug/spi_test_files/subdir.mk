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
	riscv64-unknown-elf-gcc -march=rv32im -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:\Users\mashford\Documents\GitHub\PolarFire_RISC-V_TMR_SoftConsole\NASA_RISC-V_TMR_TEST_PROG\drivers\CoreGPIO" -I"C:\Users\mashford\Documents\GitHub\PolarFire_RISC-V_TMR_SoftConsole\NASA_RISC-V_TMR_TEST_PROG\drivers\CoreI2C" -I"C:\Users\mashford\Documents\GitHub\PolarFire_RISC-V_TMR_SoftConsole\NASA_RISC-V_TMR_TEST_PROG\drivers\CoreSPI" -I"C:\Users\mashford\Documents\GitHub\PolarFire_RISC-V_TMR_SoftConsole\NASA_RISC-V_TMR_TEST_PROG\drivers\CoreUARTapb" -I"C:\Users\mashford\Documents\GitHub\PolarFire_RISC-V_TMR_SoftConsole\NASA_RISC-V_TMR_TEST_PROG\hal" -I"C:\Users\mashford\Documents\GitHub\PolarFire_RISC-V_TMR_SoftConsole\NASA_RISC-V_TMR_TEST_PROG\riscv_hal" -I"C:\Users\mashford\Documents\GitHub\PolarFire_RISC-V_TMR_SoftConsole\NASA_RISC-V_TMR_TEST_PROG\drivers\CoreTimer" -I"C:\Users\mashford\Documents\GitHub\PolarFire_RISC-V_TMR_SoftConsole\NASA_RISC-V_TMR_TEST_PROG\i2c_test_files" -I"C:\Users\mashford\Documents\GitHub\PolarFire_RISC-V_TMR_SoftConsole\NASA_RISC-V_TMR_TEST_PROG\spi_test_files" -I"C:\Users\mashford\Documents\GitHub\PolarFire_RISC-V_TMR_SoftConsole\NASA_RISC-V_TMR_TEST_PROG\user_handler_files" -I"C:\Users\mashford\Documents\GitHub\PolarFire_RISC-V_TMR_SoftConsole\NASA_RISC-V_TMR_TEST_PROG\lcd_test_files" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


