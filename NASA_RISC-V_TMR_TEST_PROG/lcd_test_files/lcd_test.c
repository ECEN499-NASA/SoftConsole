#include "lcd_test.h"
#include "spi_test_prog.h"

void lcd_command(int command)
{
	//Take control of SPI
	//The RS pin on the LCD needs to be set to 0
	for(int serialcounter = 1; serialcounter <= 8; serialcounter++)
	{
		if((command&0x80)==0x80)
		{
			//SerialInput pin set to 1
		}
		else
		{
			//SerialInput pin set to 0
		}
		command = (command<<1);
		//SerialClock pin to 0
		//SerialClock pin to 1
		//SerialClock pin to 0
	}
	//Release control of SPI
}

void lcd_write(int message)
{
	//Take control of SPI
		//The RS pin on the LCD needs to be set to 1
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
		//Release control of SPI
}

void lcd_init(void)
{
	//LCD Rst to 0
	//delay(2);
	//LCD Rst to 1
	//delay(20);
	lcd_command(0x30);
	//delay(2);
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
