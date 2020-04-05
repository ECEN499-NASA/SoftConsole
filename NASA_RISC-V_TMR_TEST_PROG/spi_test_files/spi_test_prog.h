/**
 * @file 	spi_test_prog.h
 * @author	Zac Carico
 * @date 	Mar 16 2020
 * 
 * @brief	Header file containing all the prototypes 
 * 			and declarations for the SPI test
 */

#ifndef SPI_TEST_PROG_H
#define SPI_TEST_PROG_H

#include <string.h>
#include <stdlib.h>
#include "hw_platform.h"
#include "core_uart_apb.h"
#include "core_spi.h"
#include "user_handler.h"

/**
 * @brief	Structure used to store SPI device configurations
 */
typedef struct {
	spi_instance_t *spi; /**< SPI object device is connected to */
	spi_slave_t spi_sel; /**< Device's select number */
} spi_dev;

/**
 * @brief	List of available SPIs of the microcontroller
 * 
 * @details The order of the list is crucial. It is the same order as the select lines.
 */
typedef enum {
	FRAM,
	EXTERNAL_SPI_0,
	EXTERNAL_SPI_1,
	ADC,
	LCD_SCREEN,
	ACCELEROMETER
} SPI_DEVICE_ID;

/**
 * @brief	List of different commands the user can perform
 */
typedef enum {
	SEND_WRITE_COMM,
	SEND_READ_COMM
} SPI_TEST_SEL;

/** @brief Object for the RISC-V core's SPI hardware */
spi_instance_t riscv_spi;

/** @brief Current device selected to read/write data */
spi_dev *selected_dev;

/** @brief ID of the currently selected device. 
 * Used to tell the user what device is currently 
 * selected 
 */
SPI_DEVICE_ID selected_dev_id;

/** @brief Used to determine if the user wants to quit the test program */
uint8_t quit_spi_test;

/** @brief Command byte to send over SPI */
uint8_t spi_command_byte;

extern UART_instance_t g_uart;
extern spi_dev fram_dev;
extern spi_dev external_spi_0;
extern spi_dev external_spi_1;
extern spi_dev adc_dev;
extern spi_dev lcd_screen_dev;
extern spi_dev accelerometer_dev;

void spi_test_init(void);
void spi_test_read(spi_dev *device, uint8_t *command, uint8_t *data, uint8_t data_size);
void spi_test_write(spi_dev *device, uint8_t *data, uint8_t data_size, uint8_t *resp_data);
void spi_test_handler(void);
void spi_test_send_write_command(void);
void spi_test_send_read_command(void);
void spi_test_display_write_command_instructions(void);
void spi_test_write_single_byte(void);
void spi_test_write_quad_byte(void);
void spi_test_write_custom_byte(void);
void spi_test_display_read_command_instructions(void);
void spi_test_read_single_byte(void);
void spi_test_read_quad_byte(void);
void spi_test_read_custom_byte(void);
void spi_test_display_commands(void);
void spi_test_display_devices(void);
void spi_test_display_selected_device(void);
void spi_test_change_selected_device(void);
void spi_test_display_incorrect_command(void);

#endif /*SPI_TEST_PROG_H*/
