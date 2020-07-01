/**
 * @file    lcd_test.c
 * @date    Apr 7, 2020
 * @author  Michael Ashford
 *
 * @brief   Function definitions of lcd_test.h
 */

#include <time.h>
#include "core_gpio.h"
#include "lcd_test.h"
#include "spi_test_prog.h"
#include "gpio_test_routine.h"

#define RS      28  //FMC E3
#define RST     29

/**
 * @brief   Send a command to the LCD
 *
 * @warning Need to change the first line so it changes the FMC E3 pin.
 */
void lcd_command(uint8_t command)
{
    uint8_t response = 0;
    uint8_t writeData[1] = {command};
    GPIO_set_output(&g_gpio,RS,0);
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
    uint8_t writeData[1] = {message};
    uint8_t response = 0;
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\n\rSelect LCD Screen\n\r");
	spi_test_change_selected_device();
    GPIO_set_output(&g_gpio,RS,1);
    spi_test_write(&lcd_screen_dev, message, 1, response);
}

/**
 * @brief   Initial setup of the LCD Screen
 *
 * @details Needs to be run each time the FPGA is powered up with the PCB in.
 *
 */
void lcd_init(void)
{
    //initialize gpio
    gpio_test_init();

	UART_polled_tx_string(&g_uart, (const uint8_t *)"\n\rSelect LCD Screen\n\r");
	spi_test_change_selected_device();
	//LCD Rst to 0
	GPIO_set_output(&g_gpio,RST,0);

	nanosleep((const struct timespec[]){{0, 2000000L}}, NULL);
	//LCD Rst to 1
    GPIO_set_output(&g_gpio,RST,1);

    nanosleep((const struct timespec[]){{0, 20000000L}}, NULL);
	lcd_command(0x30);
	nanosleep((const struct timespec[]){{0, 2000000L}}, NULL);
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
	nanosleep((const struct timespec[]){{0, 10000000L}}, NULL);
}

/**
 * @brief   Display "Hello World" on the LCD
 *
 * @warning Needs to be finished.
 *
 */
void lcd_test(unsigned char* message, int length, int line)
{
   lcd_init();
   
   if (line == 0)
   {
	  int col;
      for (col = 0; col < length; col = col + 1)
      {
         // Set the DDRAM address
         lcd_command(0x80 | col);
         lcd_write(*(message++));
      }
   }
   
   else if (line == 1)
   {
	  int col;
      for (col = 0; col < length; col = col + 1)
      {
         lcd_command(0xC0 | col);
         lcd_write(*(message++));
      }
   }
   
   /* "Hello           "
   char row1[16] = {0x48, 0x65, 0x6C, 0x6C, 0x6F, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0};
   // "World!          "
   char row2[16] = {0x57, 0x6F, 0x72, 0x6C, 0x64, 0x21, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0};
   
   // Write to row 1
   char col;
   for (col = 0; col < 16; col = col + 1)
   {
      // Set the DDRAM address
      lcd_command(0x80 | col);
      lcd_write(row1[col]);
   }
   
   // Write to row 2
   for (col = 0; col < 16; col = col + 1)
   {
      lcd_command(0xC0 | col);
      lcd_write(row2[col]);
   }
    */
}
