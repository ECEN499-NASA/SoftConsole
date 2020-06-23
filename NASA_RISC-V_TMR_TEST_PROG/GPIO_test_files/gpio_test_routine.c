/**
 * @file 	gpio_test_routine.c
 * @date 	June 4, 2020
 * @author	Chris Porter
 *
 * @brief	Function definitions of gpio_test_routine.h
 */

#include "gpio_test_routine.h"
#include "hal.h"
#include "hw_platform.h"
#include "core_gpio.h"
#include "riscv_hal.h"
#include "core_timer.h"
#include "core_uart_apb.h"
#include "user_handler.c"

//gpio_instance_t this_gpio;


/**
 * @brief   Initializes the GPIO test. First function called
 *          in the test's main function.
 *
 * @details Used to initialize and configure the GPIO
 */
void gpio_test_init(gpio_instance_t *this_gpio)
{
    GPIO_init(this_gpio , COREGPIO_BASE_ADDR, GPIO_APB_32_BITS_BUS);
    GPIO_config(this_gpio, GPIO_0, GPIO_INPUT_MODE);
    GPIO_config(this_gpio, GPIO_1, GPIO_OUTPUT_MODE);
    GPIO_config(this_gpio, GPIO_2, GPIO_INOUT_MODE);
//    GPIO_config(this_gpio, GPIO_5, GPIO_INOUT_MODE);
//    GPIO_config(this_gpio, GPIO_3, GPIO_INOUT_MODE);
//    GPIO_config(this_gpio, GPIO_4, GPIO_INOUT_MODE);
//    GPIO_config(this_gpio, GPIO_6, GPIO_INOUT_MODE);
//    GPIO_config(this_gpio, GPIO_7, GPIO_INOUT_MODE);
//    GPIO_config(this_gpio, GPIO_8, GPIO_INOUT_MODE);
//    GPIO_config(this_gpio, GPIO_9, GPIO_INOUT_MODE);
//    GPIO_config(this_gpio, GPIO_10, GPIO_INOUT_MODE);
//    GPIO_config(this_gpio, GPIO_11, GPIO_INOUT_MODE);
//    GPIO_config(this_gpio, GPIO_12, GPIO_INOUT_MODE);
//    GPIO_config(this_gpio, GPIO_13, GPIO_INOUT_MODE);
//    GPIO_config(this_gpio, GPIO_14, GPIO_INOUT_MODE);
//    GPIO_config(this_gpio, GPIO_15, GPIO_INOUT_MODE);
//    GPIO_config(this_gpio, GPIO_16, GPIO_INOUT_MODE);
//    GPIO_config(this_gpio, GPIO_17, GPIO_INOUT_MODE);
//    GPIO_config(this_gpio, GPIO_18, GPIO_INOUT_MODE);
//    GPIO_config(this_gpio, GPIO_19, GPIO_INOUT_MODE);
//    GPIO_config(this_gpio, GPIO_20, GPIO_INOUT_MODE);
//    GPIO_config(this_gpio, GPIO_21, GPIO_INOUT_MODE);
//    GPIO_config(this_gpio, GPIO_22, GPIO_INOUT_MODE);
//    GPIO_config(this_gpio, GPIO_23, GPIO_INOUT_MODE);
//    GPIO_config(this_gpio, GPIO_24, GPIO_INOUT_MODE);
//    GPIO_config(this_gpio, GPIO_25, GPIO_INOUT_MODE);
//    GPIO_config(this_gpio, GPIO_26, GPIO_INOUT_MODE);
//    GPIO_config(this_gpio, GPIO_27, GPIO_INOUT_MODE);
//    GPIO_config(this_gpio, GPIO_28, GPIO_INOUT_MODE);
//    GPIO_config(this_gpio, GPIO_29, GPIO_INOUT_MODE);
//    GPIO_config(this_gpio, GPIO_30, GPIO_INOUT_MODE);
//    GPIO_config(this_gpio, GPIO_31, GPIO_INOUT_MODE);
}

/**
 * @brief   Reads the GPIO Inputs
 *
 * @details The function will read the input GPIO and display the results
 *
 * @code
 *
 * @param this_gpio gpio_instance_t holds the information about the GPIO module.
 *
 * @return void
 */
void gpio_test_read(gpio_instance_t *this_gpio)
{
    uint32_t gpio_inputs;
    gpio_inputs = GPIO_get_inputs(this_gpio);
    UART_polled_tx_string(&g_uart, (const uint8_t *)"Inputs are:");
    UART_polled_tx_string(&g_uart, (const uint8_t *)gpio_inputs);

}

/**
 * @brief   Writes to the GPIO outputs
 *
 * @details Writes 1 to GPIO_1 of this_gpio.
 *
 * @code

 * @endcode
 *
 * @param this_gpio gpio_instance_t holds the information about the GPIO module.
 */
void gpio_test_write_1_high(gpio_instance_t *this_gpio)
{
    UART_polled_tx_string(&g_uart, (const uint8_t *)"\n\rWriting 1 to GPIO_1\n\r");
    uint32_t gpio_outputs;
    gpio_outputs = GPIO_get_outputs(this_gpio);
    gpio_outputs = gpio_outputs | GPIO_1_MASK;
    GPIO_set_outputs(this_gpio, gpio_outputs);
}

void gpio_test_write_1_low(gpio_instance_t *this_gpio)
{
    UART_polled_tx_string(&g_uart, (const uint8_t *)"\n\rWriting 0 to GPIO_1\n\r");
    uint32_t gpio_outputs;
    gpio_outputs = GPIO_get_outputs(this_gpio);
    gpio_outputs = gpio_outputs | GPIO_1_MASK;
    GPIO_set_outputs(this_gpio, gpio_outputs);
}

void gpio_test_write(gpio_instance_t *this_gpio)
{
//    uint32_t pin;
//    uint32_t val;
//    uint8_t dec_place = 2;
//    UART_polled_tx_string(&g_uart, (const uint8_t *)"\n\r Which pin would you like to set?\n\r");
//    pin = get_dec_from_user(dec_place);
//    UART_polled_tx_string(&g_uart, (const uint8_t *)"\n\r What value to write to it?/n/r");
//    val = get_dec_from_user(1);
//
//    GPIO_set_output(this_gpio, pin, val);
}

/**
 * @brief   The main function of the "gpio_TEST_PROG". Lets user change
 *          settings and test different aspects of the SDI
 */
void gpio_test_handler(void)
{
    char command = 0;
    gpio_instance_t *this_gpio;

    UART_polled_tx_string(&g_uart, (const uint8_t *)"\n\rWELCOME TO THE GPIO TEST!\n\r");
    gpio_test_display_commands();
    gpio_test_init(this_gpio);

    while(quit_gpio_test == 0)
    {
        UART_polled_tx_string(&g_uart, (const uint8_t *)"\n\r What would you like to do?\n\r");
        command = get_single_char_from_user();
        switch(command)
        {
            case 'h':
                gpio_test_display_commands();
                break;
            case 'q':
                quit_gpio_test = 1;
                break;
            case '1':
                gpio_test_write_1_high(this_gpio);
                break;
            case '2':
                gpio_test_write_1_low(this_gpio);
                break;
            case 'w':
                gpio_test_write(this_gpio);
                break;
            case 'r':
                gpio_test_read(this_gpio);
                break;
            default:
                gpio_test_display_incorrect_command();
                break;
        }
    }

    UART_polled_tx_string(&g_uart, (const uint8_t *)"\n\rLeaving gpio Test Program\n\r");
    return;
}

/**
 * @brief   Displays the gpio_TEST_PROG top-level commands
 */
void gpio_test_display_commands(void)
{
    UART_polled_tx_string(&g_uart, (const uint8_t *)"\tCOMMANDS:\n\r");
    UART_polled_tx_string(&g_uart, (const uint8_t *)"\t- w\t write to GPIO\n\r");
    UART_polled_tx_string(&g_uart, (const uint8_t *)"\t- r\t read from GPIO\n\r");
    UART_polled_tx_string(&g_uart, (const uint8_t *)"\t- h\t display these commands\n\r");
    UART_polled_tx_string(&g_uart, (const uint8_t *)"\t- q\t exit gpio Test Program\n\r");
}

/**
 * @brief Used when the user enters an invalid command
 */
void gpio_test_display_incorrect_command(void)
{
    UART_polled_tx_string(&g_uart, (const uint8_t *)"ERROR! Invalid Command!\n\r");
}
