#include "riscv_hal.h"
#include "core_uart_apb.h"
#include "core_gpio.h"
#include "hw_reg_access.h"
#include "hw_platform.h"
#include "gpio_test_routine.h"
#include "i2c_test_routine.h"
#include "spi_test_prog.h"
#include "user_handler.h"
#include "lcd_test.h"
#include "uart_test_routine.h"


/**
 * @brief	Used to list the different kinds of tests a user can use. 
 * 			Also used to help clarify the switch statement to the 
 * 			programmer.
 */
typedef enum{
	GPIO_TEST,
	I2C_TEST,
	SPI_TEST,
	UART_TEST,
	LVDS_UART_TEST,
	ADC_TEST,
	SENSORS_TEST,
	LCD_SCREEN_TEST,
	CPU_TEST,
	UNIT_TEST
} TEST_ID;

/*
 * Delay loop down counter load value.
 */
#define DELAY_LOAD_VALUE     0x00080000

/*-----------------------------------------------------------------------------
 * UART instance data.
 */
UART_instance_t g_uart;

/*-----------------------------------------------------------------------------
 * GPIO instance data.
 */
gpio_instance_t g_gpio_out;


// PROTOTYPES
void displayIncorrectCommand(void);
void testProgramManager(void);
void displayTestList(void);
void displayTestUnavailable(void);
void displayCommandsList(void);

/*-----------------------------------------------------------------------------
 * main
 */
int main()
{
    volatile int32_t delay_count = 0;
    volatile uint8_t print_flag = 0;
    volatile uint8_t tool = 0;
#if 1
    /**************************************************************************
     * Initialize the CoreGPIO driver with the base address of the CoreGPIO
     * instance to use and the initial state of the outputs.
     *************************************************************************/
    GPIO_init(&g_gpio_out, COREGPIO_BASE_ADDR, GPIO_APB_32_BITS_BUS);

    /**************************************************************************
     * Configure the GPIOs.
     *************************************************************************/
    GPIO_config( &g_gpio_out, GPIO_0, GPIO_OUTPUT_MODE );
    GPIO_config( &g_gpio_out, GPIO_1, GPIO_OUTPUT_MODE );
    GPIO_config( &g_gpio_out, GPIO_2, GPIO_OUTPUT_MODE );
    GPIO_config( &g_gpio_out, GPIO_3, GPIO_OUTPUT_MODE );

    /**************************************************************************
     * Set the GPIO outputs.
     *************************************************************************/
    GPIO_set_output( &g_gpio_out, GPIO_0,1 );
    GPIO_set_output( &g_gpio_out, GPIO_1,0 );
    GPIO_set_output( &g_gpio_out, GPIO_2,1 );
    GPIO_set_output( &g_gpio_out, GPIO_3,0 );


    /**************************************************************************
     * Initialize CoreUARTapb with its base address, baud value, and line
     * configuration.
     *************************************************************************/
    UART_init(&g_uart,
    		  COREUARTAPB0_BASE_ADDR,
			  BAUD_VALUE_115200,
			  (DATA_8_BITS | NO_PARITY));

#endif
    /*
     * Infinite loop.
     */
    for(;;)
    {
    	displayCommandsList();
    	testProgramManager();
    }
    return 0;
}

/**
 * @brief	Manages what test to enter depending on the user's input.
 */
void testProgramManager(void)
{
	uint8_t invalidCommand = 1;

	while(invalidCommand)
	{
		UART_polled_tx_string(&g_uart, (const uint8_t *)"Enter a TestID to begin testing\n\r");
		char input = get_single_char_from_user();
		uint8_t test = (uint8_t)input - '0';
		uint8_t isTestID = 0;

		switch(input)
		{
			case 'h':
				displayCommandsList();
				break;
			case 'd':
				displayTestList();
				break;
			default:
				isTestID = 1;
				break;
		}

		if(isTestID)
		{
			switch(test)
			{
				case GPIO_TEST:
				    gpio_test_handler();
					break;
				case I2C_TEST:
					run_i2c_test();
					break;
				case SPI_TEST:
					spi_test_handler();
					break;
				case UART_TEST:
					displayTestUnavailable();
					break;
				case LVDS_UART_TEST:
					run_uart_test();
					break;
				case ADC_TEST:
					displayTestUnavailable();
					break;
				case SENSORS_TEST:
					displayTestUnavailable();
					break;
				case LCD_SCREEN_TEST:
					lcd_test();
					break;
				case CPU_TEST:
					displayTestUnavailable();
					break;
				case UNIT_TEST:
					user_handler_unit_test_handler();
					break;
				default:
					displayIncorrectCommand();
					break;
			}
		}
	}
}

/**
 * @brief	Used when user enters an invalid command
 */
void displayIncorrectCommand(void)
{
	UART_polled_tx_string(&g_uart, (const uint8_t *)"ERROR! Invalid Command!\n\r");
}

/**
 * @brief	Used to display the list and command of different tests a user to perform
 */
void displayTestList(void)
{
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\tTEST IDs:\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\t-(0) GPIO_TEST\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\t-(1) I2C_TEST\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\t-(2) SPI_TEST\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\t-(3) UART_TEST\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\t-(4) LVDS_UART_TEST\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\t-(5) ADC_TEST\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\t-(6) SENSOR_TEST\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\t-(7) LCD_SCREEN_TEST\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\t-(8) CPU_TEST\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\t-(9) UNIT_TEST\n\r");
}

/**
 * @brief	Used to tell the user that the selected test hasn't been programed yet
 */
void displayTestUnavailable(void)
{
	UART_polled_tx_string(&g_uart,
			(const uint8_t *)"ERROR! Test Not programmed at this time...\n\r");
}

/**
 * @brief	Displays list of commands a user can perform
 */
void displayCommandsList(void)
{
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\tCOMMANDS:\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\t- h\t display these commands\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\t- d\t display tests IDs\n\r");
}

