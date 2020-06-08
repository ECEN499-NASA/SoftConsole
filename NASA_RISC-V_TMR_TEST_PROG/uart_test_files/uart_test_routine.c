/**
 * @file 	uart_test_routine.c
 * @date 	May 16, 2020
 * @author	Spencer Cheney
 *
 * @brief	Function definitions of uart_test_routine.h
 */

#include "uart_test_routine.h"
#include "hal.h"
#include "hw_platform.h"
#include "riscv_hal.h"
#include "core_timer.h"
#include "core_uart_apb.h"


int run_uart_test(void)
{
	uint8_t rx_size=0;
	uint8_t rx_buffer[1];
	uint8_t loop_count;
	uint8_t err_status;
	// PLIC Initialization
	PLIC_init();
	UART_init(&g_core_uart, LVDS_UART_BASE_ADDR, BAUD_VALUE_57600, (DATA_8_BITS | EVEN_PARITY));

	// Initialize the system tick for 10mS operation or 1 tick every 100th of
	// a second and also make sure it is lower priority than the I2C IRQs.
	SysTick_Config(SYS_CLK_FREQ / 2);

	/* CoreI2C Master*/
	PLIC_SetPriority(External_5_IRQn, 1);
	PLIC_EnableIRQ(External_5_IRQn);
	// Enable interrupts in general.
	HAL_enable_interrupts();

	// Display the initial information about the demo followed by the main
	// menu.
	display_greeting();
	select_mode_uart();
	for(loop_count=0; loop_count < BUFFER_SIZE; loop_count++)
	{
		//g_slave_rx_buffer[loop_count] = 0x00;
		rx_buf[loop_count] = 0x00;
		tx_buf[loop_count] = 0x00;
	}

	do
	{
		rx_size = UART_get_rx(&g_uart, rx_buffer, sizeof(rx_buffer));
		if(rx_size > 0)
		{
			switch(rx_buffer[0])
			{
				case '1':
					UART_polled_tx_string(&g_uart, (const uint8_t *)"\n\rMT-SR Mode is Selected\n\r");
					err_status = UART_get_rx_status(&g_uart);
					g_tx_length = get_data();
					if(UART_APB_NO_ERROR == err_status) {
						if(0 == g_tx_length)
						{
							UART_polled_tx_string(&g_uart, (const uint8_t *)"0 Byte Data Write Successful\n\r");
						}
						else
						{
							UART_polled_tx_string(&g_uart, (const uint8_t *)"Data Write Successful and Data is: ");
							//UART_send(&g_uart, g_slave_rx_buffer, g_tx_length);
							UART_polled_tx_string(&g_uart, (const uint8_t *)"\n\r");
						}
						UART_polled_tx_string(&g_uart, (const uint8_t*)"------------------------------------------------------------------------------\n\r");
					}
					else {
						// Distinguish between an identified failure, a time out and just to be paranoid
						// none of the above.
						if(UART_APB_PARITY_ERROR == err_status)
						{
							UART_polled_tx_string(&g_uart, (const uint8_t *)"Data Write Parity Error!\n\r");
						}
						else if(UART_APB_OVERFLOW_ERROR == err_status)
						{
							UART_polled_tx_string(&g_uart, (const uint8_t *)"Data Write Overflow Error!\n\r");
						}
						else if (UART_APB_FRAMING_ERROR == err_status)
						{
							UART_polled_tx_string(&g_uart, (const uint8_t *)"Data Write Framing Error!\n\r");
						}
						else
						{
							UART_polled_tx_string(&g_uart, (const uint8_t *)"Data Write Unknown Response!\n\r");
						}

						UART_polled_tx_string(&g_uart, (const uint8_t*)"\n\r------------------------------------------------------------------------------\n\r");
					}
					break;
				case '2':
					break;
				case '3':
					// To Exit from the application
					UART_polled_tx_string(&g_uart, (const uint8_t *)"\n\rReturn from the Main function \n\r\n\r");
					break;
				default:
					//invalid input
					UART_polled_tx_string(&g_uart, (const uint8_t *)"\n\rEnter A Valid Key: 1, 2 or 3\n\r");
					select_mode_uart();
					break;
			}
		}
	} while(rx_buffer[0] !='3');
}

/**
 * @brief	Display greeting message when application is started.
 */
static void display_greeting(void)
{
	UART_polled_tx_string(&g_uart, (const uint8_t*)"\n\r******************************************************************************\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t*)"**************************** Core UART Example ********************************\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t*)"******************************************************************************\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t*)"This example project Demonstrates the use of UART in Different Modes\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t*)"CoreUART0 is configured in Master Mode and CoreUART1 is configured in Slave Mode\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t*)"\n\r------------------------------------------------------------------------------\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t*)"************* UART Modes supported by this example project are ****************\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t*)"1. MT-SR :- Transmit\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t*)"2. MR-ST :- Receive\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t*)"------------------------------------------------------------------------------\n\r");
}

/**
 * @brief	Select the I2C Mode.
 */
static void select_mode_uart(void)
{
	UART_polled_tx_string(&g_uart, (const uint8_t*)"\n\r*********************** Select the UART Mode to perform ***********************\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t*)"Press Key '1' to perform MT-SR (Transmit)\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t*)"Press Key '2' to perform MR-ST (Receive)\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t*)"Press Key '3' to EXIT from the Application \n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t*)"------------------------------------------------------------------------------\n\r");
}

/**
 * @brief	Function to get the key from user
 */
uint8_t get_data()
{
	uint8_t complete = 0;
	uint8_t rx_buffer[1];
	uint8_t count=0;
	uint8_t rx_size=0;


	// Read the key strokes entered by user and store them for transmission to the
	// slave.
	UART_polled_tx_string(&g_uart, (const uint8_t*)"\n\rEnter up to 32 characters to write to UART1: ");
	count = 0;
	while(!complete)
	{
		rx_size = UART_get_rx(&g_uart, rx_buffer, sizeof(rx_buffer));
		if(rx_size > 0)
		{
			UART_send(&g_uart, rx_buffer, sizeof(rx_buffer));

			// Is it to terminate from the loop
			if(ENTER == rx_buffer[0])
			{
				complete = 1;
			}
			// Is a character to add to our transmit string
			else
			{
				tx_buf[count] = rx_buffer[0];
				count++;
				if(32 == count)
				{
				   complete = 1;
				}
			}
		}
	}

	UART_polled_tx_string(&g_uart, (const uint8_t*)"\n\r");

	return(count);
}

/**
 * @brief	Display "Press any key to continue." message and wait for key press.
 */
void press_any_key_to_continue(void)
{
	size_t rx_size;
	uint8_t rx_char;
	uint8_t press_any_key_msg[] = "\n\rPress any key to continue.";

	UART_send(&g_uart, press_any_key_msg, sizeof(press_any_key_msg));
	do {
		rx_size = UART_get_rx(&g_uart, &rx_char, sizeof(rx_char));
	} while(rx_size == 0);
	select_mode_uart();
}

/**
 * @brief	Interrupt handler. Not sure what this does when called though...
 */
uint8_t External_6_IRQHandler(void)
{
	//I2C_isr(&g_core_i2c1);
	return (EXT_IRQ_KEEP_ENABLED);
}