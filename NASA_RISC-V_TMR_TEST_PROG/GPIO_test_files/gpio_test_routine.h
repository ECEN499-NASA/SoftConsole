/**
 * @file 	gpio_test_routine.h
 * @date 	June 4, 2020
 * @author	Chris Porter
 *
 * @brief	Header file containing all the prototypes 
 * 			and declarations for the I2C test
 */

#ifndef GPIO_TEST_ROUTINE_H_
#define GPIO_TEST_ROUTINE_H_

#include "core_gpio.h"
#include "core_uart_apb.h"



/** @brief Object for the RISC-V core's gpio hardware */
extern gpio_instance_t g_gpio;

/** @brief Used to determine if the user wants to quit the test program */
uint8_t quit_gpio_test;

extern UART_instance_t g_uart;

void gpio_test_init(void);
void gpio_test_read(void);
void gpio_test_write_1_high(void);
void gpio_test_write_1_low(void);
void gpio_test_write(void);
void gpio_test_handler(void);
void gpio_test_display_commands(void);
void gpio_test_display_incorrect_command(void);

#endif /*GPIO_TEST_ROUTINE_H_*/
