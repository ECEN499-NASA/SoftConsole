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
 * @brief	Structure used to create a SPI "object"
 */
typedef struct {
	spi_instance_t *spi;
	spi_slave_t spi_sel;
} spi_dev;

/**
 * @brief	List of available SPIs of the microcontroller
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

/**
 * @note	Global variables used by SPI test program
 */
spi_instance_t riscv_spi;
spi_dev *selected_dev;
SPI_DEVICE_ID selected_dev_id;
uint8_t quit_spi_test;
uint8_t spi_command_byte;

/**
 * @note	These global variables are declared and 
 * 			initialized in spi_test_prog.c
 */
extern UART_instance_t g_uart;
extern spi_dev fram_dev;
extern spi_dev external_spi_0;
extern spi_dev external_spi_1;
extern spi_dev adc_dev;
extern spi_dev lcd_screen_dev;
extern spi_dev accelerometer_dev;

/**
 * @note	Function prototypes
 */
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
