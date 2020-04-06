#include <time.h>
#include "lcd_test.h"
#include "spi_test_prog.h"

void lcd_command(int command)
{
	//TODO The RS pin on the LCD (FMC E3) needs to be set to 0
	spi_test_write()
}

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

void lcd_init(void)
{
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\n\rSelect LCD Screen\n\r");
	spi_test_change_selected_device();
	//LCD Rst to 0
	nanosleep((const struct timespec[]){{0, 2000000L}}, NULL);
	//LCD Rst to 1
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
	//delay(10);
}

void lcd_test(void)
{
	lcd_write(0x00);
}
