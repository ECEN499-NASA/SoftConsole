################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../riscv_hal/init.c \
../riscv_hal/riscv_hal.c \
../riscv_hal/riscv_hal_stubs.c \
../riscv_hal/syscall.c 

S_UPPER_SRCS += \
../riscv_hal/entry.S 

OBJS += \
./riscv_hal/entry.o \
./riscv_hal/init.o \
./riscv_hal/riscv_hal.o \
./riscv_hal/riscv_hal_stubs.o \
./riscv_hal/syscall.o 

S_UPPER_DEPS += \
./riscv_hal/entry.d 

C_DEPS += \
./riscv_hal/init.d \
./riscv_hal/riscv_hal.d \
./riscv_hal/riscv_hal_stubs.d \
./riscv_hal/syscall.d 


# Each subdirectory must supply rules for building sources it contributes
riscv_hal/%.o: ../riscv_hal/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross Assembler'
	riscv64-unknown-elf-gcc -march=rv32im -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -x assembler-with-cpp -I"C:\ECEN499-TeamE\SoftConsole\SoftConsole\NASA_RISC-V_TMR_TEST_PROG\drivers\CoreTimer" -I"C:\ECEN499-TeamE\SoftConsole\SoftConsole\NASA_RISC-V_TMR_TEST_PROG\i2c_test_files" -I"C:\ECEN499-TeamE\SoftConsole\SoftConsole\NASA_RISC-V_TMR_TEST_PROG\spi_test_files" -I"C:\ECEN499-TeamE\SoftConsole\SoftConsole\NASA_RISC-V_TMR_TEST_PROG\user_handler_files" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

riscv_hal/%.o: ../riscv_hal/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv64-unknown-elf-gcc -march=rv32im -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:\ECEN499-TeamE\SoftConsole\SoftConsole\NASA_RISC-V_TMR_TEST_PROG\drivers\CoreGPIO" -I"C:\ECEN499-TeamE\SoftConsole\SoftConsole\NASA_RISC-V_TMR_TEST_PROG\uart_test_files" -I"C:\ECEN499-TeamE\SoftConsole\SoftConsole\NASA_RISC-V_TMR_TEST_PROG\drivers\CoreI2C" -I"C:\ECEN499-TeamE\SoftConsole\SoftConsole\NASA_RISC-V_TMR_TEST_PROG\drivers\CoreSPI" -I"C:\ECEN499-TeamE\SoftConsole\SoftConsole\NASA_RISC-V_TMR_TEST_PROG\drivers\CoreUARTapb" -I"C:\ECEN499-TeamE\SoftConsole\SoftConsole\NASA_RISC-V_TMR_TEST_PROG\hal" -I"C:\ECEN499-TeamE\SoftConsole\SoftConsole\NASA_RISC-V_TMR_TEST_PROG\riscv_hal" -I"C:\ECEN499-TeamE\SoftConsole\SoftConsole\NASA_RISC-V_TMR_TEST_PROG\drivers\CoreTimer" -I"C:\ECEN499-TeamE\SoftConsole\SoftConsole\NASA_RISC-V_TMR_TEST_PROG\i2c_test_files" -I"C:\ECEN499-TeamE\SoftConsole\SoftConsole\NASA_RISC-V_TMR_TEST_PROG\GPIO_test_files" -I"C:\ECEN499-TeamE\SoftConsole\SoftConsole\NASA_RISC-V_TMR_TEST_PROG\spi_test_files" -I"C:\ECEN499-TeamE\SoftConsole\SoftConsole\NASA_RISC-V_TMR_TEST_PROG\user_handler_files" -I"C:\ECEN499-TeamE\SoftConsole\SoftConsole\NASA_RISC-V_TMR_TEST_PROG\lcd_test_files" -include"C:\ECEN499-TeamE\SoftConsole\SoftConsole\NASA_RISC-V_TMR_TEST_PROG\uart_test_files\uart_test_routine.h" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


