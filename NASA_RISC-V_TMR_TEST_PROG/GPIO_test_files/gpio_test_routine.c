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


/**
 * @brief   Initializes the GPIO test. First function called
 *          in the test's main function.
 *
 * @details Used to initialize the GPIO
 */
void gpio_test_init(void)
{

}

/**
 * @brief   Reads x bytes (x specified by the data_size param)
 *
 * @details The function will send a read command to the specified
 *          device, then fill up the data param with the information
 *          coming in
 *
 * @code
    #define DATA_SIZE 10

    uint8_t data_size = DATA_SIZE;
    uint8_t data_read[DATA_SIZE];
    uint8_t read_command = 0x10; // Can be any byte-sized read command
    gpio_dev device = {
        .gpio = &riscv_gpio,      // Any "gpio_instance_t" type
        .gpio_sel = gpio_SLAVE_0  // Any "gpio_slave_t" type
    };

    gpio_test_read(&device, &command, &data_read, &data_size);
    printf("Data Read:\t0x");
    for(uint8_t i = 0; i < DATA_SIZE; i++) {
          printf(" %x", data_read[i]);
    }
    printf("\n");
 * @endcode
 *
 * @param device    Pointer to device to read data from. There are
 *                  currently 6 different devices that can be read from
 * @param command   Pointer to read command to send to the device
 * @param data      Pointer/array to be filled with incomming data
 * @param data_size Size of the data array
 *
 * @return void
 */
void gpio_test_read(gpio_dev *device)
{

}

/**
 * @brief   Writes x bytes (x specified by the data_size param)
 *
 * @details Writes data to the specified device and then captures the
 *          device's response
 *
 * @code
    #define DATA_SIZE 10

    uint8_t data_size = DATA_SIZE;
    uint8_t data[DATA_SIZE] = {
        // write_command
        0x10,
        // data
        0x00, 0x01, 0x02, 0x03, 0x04,
        0x05, 0x07, 0x08, 0x09
    };
    gpio_dev device = {
        .gpio = &riscv_gpio,      // Any "gpio_instance_t" type
        .gpio_sel = gpio_SLAVE_0  // Any "gpio_slave_t" type
    };
    uint8_t *resp_data;

    gpio_test(&device. &data, data_size, &resp_data);
    printf("Response:\t%d", resp_data);
 * @endcode
 *
 * @param device    Pointer to device to read data from. There are
 *                  currently 6 different devices that can be read from
 * @param data      Pointer/array of data to send to the device, The
 *                  first byte in the array being the write command the
 *                  device needs.
 * @param data_size Size of the data array
 * @param resp_data pointer to the device's response after receiving the data
 */
void gpio_test_write(gpio_dev *device, uint8_t *data)
{

}

/**
 * @brief   The main function of the "gpio_TEST_PROG". Lets user change
 *          settings and test different aspects of the SDI
 */
void gpio_test_handler(void)
{
    char command = 0;

    UART_polled_tx_string(&g_uart, (const uint8_t *)"\n\rWELCOME TO THE GPIO TEST!\n\r");
    gpio_test_display_commands();
    gpio_test_init();

    while(quit_gpio_test == 0)
    {
        UART_polled_tx_string(&g_uart, (const uint8_t *)"\n\r What would you like to do?\n\r");
        command = get_single_char_from_user();
        switch(command)
        {
            case 'h':
                gpio_test_display_commands();
                break;
            case 'd':
                gpio_test_display_devices();
                break;
            case 'q':
                quit_gpio_test = 1;
                break;
            case '0':
                gpio_test_change_selected_device();
                break;
            case '1':
                gpio_test_display_selected_device();
                break;
            case '2':
                gpio_test_send_write_command();
                break;
            case '3':
                gpio_test_send_read_command();
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
 * @brief   Handler for used to test sending data of various sizes
 *          to the selected device.
 *
 * @details User can choose to send data of 1byte, 4bytes, or an amount specified by the user.
 */
void gpio_test_send_write_command(void)
{
    char command = 0;

    while(quit_gpio_test == 0)
    {
        UART_polled_tx_string(&g_uart, (const uint8_t *)"You have entered the \"Send Write Command\" tool\n\r\n\r");
        gpio_test_display_write_command_instructions();
        command = get_single_char_from_user();
        switch(command)
        {
            case 'h':
                gpio_test_display_write_command_instructions();
                break;
            case 'd':
                gpio_test_display_devices();
                break;
            case 'q':
                quit_gpio_test = 1;
                break;
            case '0':
                gpio_test_change_selected_device();
                break;
            case '1':
                gpio_test_display_selected_device();
                break;
            case '2':
                gpio_test_write_single_byte();
                break;
                break;
            default:
                gpio_test_display_incorrect_command();
                break;
        }
    }

    quit_gpio_test = 0;
    UART_polled_tx_string(&g_uart, (const uint8_t *)"\n\rWELCOME TO THE gpio TEST!\n\r");
}

/**
 * @brief   Handler for used to test reading data of various sizes
 *          from the selected device.
 *
 * @details User can choose to read data of 1byte, 4bytes, or an amount specified by the user.
 */
void gpio_test_send_read_command(void)
{
    char command = 0;

    while(quit_gpio_test == 0)
    {
        UART_polled_tx_string(&g_uart, (const uint8_t *)"You have entered the \"Send Write Command\" tool\n\r\n\r");
        gpio_test_display_write_command_instructions();
        command = get_single_char_from_user();
        switch(command)
        {
            case 'h':
                gpio_test_display_read_command_instructions();
                break;
            case 'd':
                gpio_test_display_devices();
                break;
            case 'q':
                quit_gpio_test = 1;
                break;
            case '0':
                gpio_test_change_selected_device();
                break;
            case '1':
                gpio_test_display_selected_device();
                break;
            case '2':
                gpio_test_read_single_byte();
                break;
            case '3':
                gpio_test_read_quad_byte();
                break;
            case '4':
                gpio_test_read_custom_byte();
                break;
            default:
                gpio_test_display_incorrect_command();
                break;
        }
    }

    quit_gpio_test = 0;
    UART_polled_tx_string(&g_uart, (const uint8_t *)"\n\rWELCOME TO THE gpio TEST!\n\r");
}

/**
 * @brief   Displays the user commands for the program
 */
void gpio_test_display_write_command_instructions(void)
{
    UART_polled_tx_string(&g_uart, (const uint8_t *)"\tCOMMANDS:\n\r");
    UART_polled_tx_string(&g_uart, (const uint8_t *)"\t- 0\t change selected device\n\r");
    UART_polled_tx_string(&g_uart, (const uint8_t *)"\t- 1\t display selected device\n\r");
    UART_polled_tx_string(&g_uart, (const uint8_t *)"\t- 2\t write a single byte\n\r");
    UART_polled_tx_string(&g_uart, (const uint8_t *)"\t- 3\t write 4 bytes\n\r");
    UART_polled_tx_string(&g_uart, (const uint8_t *)"\t- 4\t write custom number of bytes\n\r");
    UART_polled_tx_string(&g_uart, (const uint8_t *)"\t- h\t display these commands\n\r");
    UART_polled_tx_string(&g_uart, (const uint8_t *)"\t- d\t display gpio device IDs\n\r");
    UART_polled_tx_string(&g_uart, (const uint8_t *)"\t- q\t exit \"Send Write Command\" tool\n\r");
}

/**
 * @brief   Tests just sending one byte of data determined by the user's input
 */
void gpio_test_write_single_byte(void)
{
    uint8_t writeData[1] = {0};
    uint8_t response = 0;
    uint8_t sendData = 0;
    char hexStr[5];

    UART_polled_tx_string(&g_uart, (const uint8_t *)"You have entered the \"Send Single Byte\" tool\n\r\n\r");

    while(sendData == 0)
    {
        UART_polled_tx_string(&g_uart, (const uint8_t *)"\tEnter Write Command:");
        gpio_command_byte = (uint8_t)(get_bytes_from_user(1));

        UART_polled_tx_string(&g_uart, (const uint8_t *)"\tEnter Value to write:");
        writeData[0] = (uint8_t)(get_bytes_from_user(1));

        UART_polled_tx_string(&g_uart, (const uint8_t *)"\tSend write command \"");
        int_to_single_byte_string(gpio_command_byte, hexStr);
        UART_polled_tx_string(&g_uart, (const uint8_t *)hexStr);
        UART_polled_tx_string(&g_uart, (const uint8_t *)"\" and value \"");
        int_to_single_byte_string(writeData[0], hexStr);
        UART_polled_tx_string(&g_uart, (const uint8_t *)hexStr);
        UART_polled_tx_string(&g_uart, (const uint8_t *)"\"?");
        if(get_yes_no_from_user() == 1)
            sendData = 1;
    }
    gpio_test_write(selected_dev, writeData, 1, &response);

    UART_polled_tx_string(&g_uart, (const uint8_t *)"\n\r\tData has been sent!\n\r");

    UART_polled_tx_string(&g_uart, (const uint8_t *)"\tResponse was \"");
    int_to_single_byte_string(response, hexStr);
    UART_polled_tx_string(&g_uart, (const uint8_t *)hexStr);
    UART_polled_tx_string(&g_uart, (const uint8_t *)"\"\n\r");
}

/**
 * @brief   Displays the commands that a user can select to test
 *          reading from the selected gpio device
 */
void gpio_test_display_read_command_instructions(void)
{
    UART_polled_tx_string(&g_uart, (const uint8_t *)"\tCOMMANDS:\n\r");
    UART_polled_tx_string(&g_uart, (const uint8_t *)"\t- 0\t change selected device\n\r");
    UART_polled_tx_string(&g_uart, (const uint8_t *)"\t- 1\t display selected device\n\r");
    UART_polled_tx_string(&g_uart, (const uint8_t *)"\t- 2\t read a single byte\n\r");
    UART_polled_tx_string(&g_uart, (const uint8_t *)"\t- 3\t read 4 bytes\n\r");
    UART_polled_tx_string(&g_uart, (const uint8_t *)"\t- 4\t read custom number of bytes\n\r");
    UART_polled_tx_string(&g_uart, (const uint8_t *)"\t- h\t display these commands\n\r");
    UART_polled_tx_string(&g_uart, (const uint8_t *)"\t- d\t display gpio device IDs\n\r");
    UART_polled_tx_string(&g_uart, (const uint8_t *)"\t- q\t exit \"Send Write Command\" tool\n\r");
}

/**
 * @brief   Tests reading a single byte from the selected gpio device
 */
void gpio_test_read_single_byte(void)
{
    uint8_t readData[1] = {0};
    uint8_t sendData = 0;
    char hexStr[5];

    UART_polled_tx_string(&g_uart, (const uint8_t *)"You have entered the \"Read Single Byte\" tool\n\r\n\r");

    while(sendData == 0)
    {
        UART_polled_tx_string(&g_uart, (const uint8_t *)"\tEnter Read Command:");
        gpio_command_byte = (uint8_t)(get_bytes_from_user(1));

        UART_polled_tx_string(&g_uart, (const uint8_t *)"\tSend read command \"");
        int_to_single_byte_string(gpio_command_byte, hexStr);
        UART_polled_tx_string(&g_uart, (const uint8_t *)hexStr);
        UART_polled_tx_string(&g_uart, (const uint8_t *)"\"?");
        if(get_yes_no_from_user() == 1)
            sendData = 1;
    }

    gpio_test_read(selected_dev, &gpio_command_byte, readData, 1);
    UART_polled_tx_string(&g_uart, (const uint8_t *)"\n\r\tData has been read!\n\r");

    UART_polled_tx_string(&g_uart, (const uint8_t *)"\tRead Data is \"");
    int_to_single_byte_string(readData[0], hexStr);
    UART_polled_tx_string(&g_uart, (const uint8_t *)hexStr);
    UART_polled_tx_string(&g_uart, (const uint8_t *)"\"\n\r");
}

/**
 * @brief   Displays the gpio_TEST_PROG top-level commands
 */
void gpio_test_display_commands(void)
{
    UART_polled_tx_string(&g_uart, (const uint8_t *)"\tCOMMANDS:\n\r");
    UART_polled_tx_string(&g_uart, (const uint8_t *)"\t- 0\t change selected device\n\r");
    UART_polled_tx_string(&g_uart, (const uint8_t *)"\t- 1\t display selected device\n\r");
    UART_polled_tx_string(&g_uart, (const uint8_t *)"\t- 2\t send write command\n\r");
    UART_polled_tx_string(&g_uart, (const uint8_t *)"\t- 3\t send read command\n\r");
    UART_polled_tx_string(&g_uart, (const uint8_t *)"\t- h\t display these commands\n\r");
    UART_polled_tx_string(&g_uart, (const uint8_t *)"\t- d\t display gpio device IDs\n\r");
    UART_polled_tx_string(&g_uart, (const uint8_t *)"\t- q\t exit gpio Test Program\n\r");
}

/**
 * @brief   Displays available gpio devices that the user can select
 */
void gpio_test_display_devices(void)
{
    UART_polled_tx_string(&g_uart, (const uint8_t *)"\tGPIO DEVICE IDs:\n\r");
    UART_polled_tx_string(&g_uart, (const uint8_t *)"\t-(0) GPIO\n\r");
    UART_polled_tx_string(&g_uart, (const uint8_t *)"\t-(1) SW\n\r");
    UART_polled_tx_string(&g_uart, (const uint8_t *)"\t-(2) LED\n\r");
}

/**
 * @brief Used when the user enters an invalid command
 */
void gpio_test_display_incorrect_command(void)
{
    UART_polled_tx_string(&g_uart, (const uint8_t *)"ERROR! Invalid Command!\n\r");
}

