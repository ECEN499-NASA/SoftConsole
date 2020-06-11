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

/**
 * @brief   Structure used to store gpio device configurations
 */
typedef struct {
    gpio_instance_t *gpio; /**< gpio object device is connected to */
} gpio_dev;

/**
 * @brief   List of available gpios of the microcontroller
 *
 * @details The order of the list is crucial. It is the same order as the select lines.
 */
typedef enum {
    GPIO,
    SW,
    LED
} gpio_DEVICE_ID;

/**
 * @brief   List of different commands the user can perform
 */
typedef enum {
    WRITE,
    READ
} gpio_TEST_SEL;

/** @brief Object for the RISC-V core's gpio hardware */
gpio_instance_t riscv_gpio;

/** @brief Current device selected to read/write data */
gpio_dev *selected_dev;

/** @brief ID of the currently selected device.
 * Used to tell the user what device is currently
 * selected
 */
gpio_DEVICE_ID selected_dev_id;

/** @brief Used to determine if the user wants to quit the test program */
uint8_t quit_gpio_test;

extern UART_instance_t g_uart;
extern gpio_dev GPIO;
extern gpio_dev LED;
extern gpio_dev SW;

void gpio_test_init(void);
void gpio_test_read(gpio_dev *device);
void gpio_test_write(gpio_dev *device, uint8_t *data);
void gpio_test_handler(void);
void gpio_test_send_write_command(void);
void gpio_test_send_read_command(void);
void gpio_test_display_write_command_instructions(void);
void gpio_test_write_single_byte(void);
void gpio_test_display_read_command_instructions(void);
void gpio_test_read_single_byte(void);
void gpio_test_display_commands(void);
void gpio_test_display_devices(void);
void gpio_test_display_incorrect_command(void);

#endif GPIO_TEST_ROUTINE_H_
