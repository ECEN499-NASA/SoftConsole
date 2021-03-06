/**
 * @file 	uart_test_routine.h
 * @date 	May 16, 2020
 * @author	Spencer Cheney
 *
 * @brief	Header file containing all the prototypes
 * 			and declarations for the UART test
 */

#ifndef UART_TEST_ROUTINE_H_
#define UART_TEST_ROUTINE_H_

#include "core_uart_apb.h"
#include "uart_addresses.h"

/**
 * @brief	Instance data for our  CoreUART device
 */
UART_instance_t g_core_uart;

/**
 * @brief   ASCII value for the enter key
 */
#define ENTER              13u
/**
 * @brief	 Receive buffer size.
 */
#define BUFFER_SIZE        32u

#define BAUD_VALUE_57600    25

int run_uart_test(void);
static void uart_display_greeting(void);
static void select_mode_uart(void);
uint8_t uart_get_data(void);
void uart_press_any_key_to_continue(void);

static uint8_t rx_buf[BUFFER_SIZE];
static uint8_t tx_buf[BUFFER_SIZE];

extern UART_instance_t g_uart;

/**
 * @brief	Counts of data sent by master and received by slave.
 */
static uint8_t tx_length=0x00;
static uint8_t rx_length=0x00;

#endif  /* UART_TEST_ROUTINE_H */
