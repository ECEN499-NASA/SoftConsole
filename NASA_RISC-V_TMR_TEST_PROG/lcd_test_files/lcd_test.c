/**
 * @file    lcd_test.c
 * @date    Apr 7, 2020
 * @author  Michael Ashford
 *
 * @brief   Function definitions of lcd_test.h
 */

#include <time.h>
#include "lcd_test.h"
#include "spi_test_prog.h"

/**
 * @brief   Send a command to the LCD
 *
 * @warning Need to change the first line so it changes the FMC E3 pin.
 */
void lcd_command(uint8_t command)
{
    uint8_t response = 0;
    uint8_t writeData[1] = {command};
	//TODO The RS pin on the LCD (FMC E3) needs to be set to 0
	spi_test_write(&lcd_screen_dev, writeData, 1, &response);
}

/**
 * @brief   Display a message on the LCD
 *
 * @warning This function is written from the LCD User Manual. It needs to be
 *          changed to reflect SPI commands like in the lcd_command above.
 */
void lcd_write(int message)
{
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\n\rSelect LCD Screen\n\r");
	spi_test_change_selected_device();
	//The RS pin on the LCD (FMC E3) needs to be set to 1
	for(int serialcounter = 1; serialcounter <= 8; serialcounter++)
	{
		if((message&0x80)==0x80)
		{
			//SerialInput pin set to 1
		}
		else
		{
			//SerialInput pin set to 0
		}
		message = (message<<1);
		//SerialClock pin to 0
		//SerialClock pin to 1
		//SerialClock pin to 0
	}
}

/**
 * @brief   Initial setup of the LCD Screen
 *
 * @details Needs to be run each time the FPGA is powered up with the PCB in.
 *
 */
void lcd_init(void)
{
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\n\rSelect LCD Screen\n\r");
	spi_test_change_selected_device();
	//LCD Rst to 0
	//nanosleep((const struct timespec[]){{0, 2000000L}}, NULL);
	//LCD Rst to 1
	//nanosleep((const struct timespec[]){{0, 20000000L}}, NULL);
	lcd_command(0x30);
	//nanosleep((const struct timespec[]){{0, 2000000L}}, NULL);
	lcd_command(0x30);
	lcd_command(0x30);
	lcd_command(0x39);
	lcd_command(0x14);
	lcd_command(0x56);
	lcd_command(0x6D);
	lcd_command(0x70);
	lcd_command(0x0C);
	lcd_command(0x06);
	lcd_command(0x01);
	//delay(10);
}

/**
 * @brief   Display "Hello World" on the LCD
 *
 * @warning Needs to be finished.
 *
 */
void lcd_test(void)
{
	lcd_write(0x00);
}
