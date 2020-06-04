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
 * @brief	Instance data for our  CoreI2C device
 */
i2c_instance_t g_core_i2c;

/**
 * @brief	I2C master serial address.
 */
#define MASTER_SER_ADDR     0x21

/**
 * @brief   I2C slave serial address.
 */
#define SLAVE_SER_ADDR     0x30

/**
 * @brief	 Receive buffer size.
 */
#define BUFFER_SIZE        32u

/**
 * @brief   ASCII value for the enter key
 */
#define ENTER              13u

/**
 * @brief	I2C operation time-out value in mS. Define as I2C_NO_TIMEOUT to disable the
 * time-out functionality.
 */
#define DEMO_I2C_TIMEOUT 3000u

/*-----------------------------------------------------------------------------
 * Local functions.
 */
i2c_slave_handler_ret_t slave_write_handler(i2c_instance_t *, uint8_t *, uint16_t);
i2c_status_t do_write_transaction(uint8_t, uint8_t * , uint8_t);
i2c_status_t do_read_transaction(uint8_t, uint8_t * , uint8_t);
i2c_status_t do_write_read_transaction(uint8_t , uint8_t * , uint8_t , uint8_t * , uint8_t);
static void display_greeting(void);
static void select_mode_i2c(void);
uint8_t get_data(void);
void press_any_key_to_continue(void);

/**
 * @brief	 I2C buffers. These are the buffers where data written transferred via I2C
 * will be stored. RX
 */
static uint8_t g_slave_rx_buffer[BUFFER_SIZE];
static uint8_t g_slave_tx_buffer[BUFFER_SIZE] = "<<-------Slave Tx data ------->>";
static uint8_t g_master_rx_buf[BUFFER_SIZE];
static uint8_t g_master_tx_buf[BUFFER_SIZE];

/**
 * @brief	Counts of data sent by master and received by slave.
 */
static uint8_t g_tx_length=0x00;

//end i2c sample stuff

extern UART_instance_t g_uart;


int run_i2c_test(void);




#endif  /* I2C_TEST_ROUTINE_H */
