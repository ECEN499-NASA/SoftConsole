#include "spi_test_prog.h"

#define lcd_rst 0
#define lcd_sel 1
#define lcd_input 3

void init()
{

}

void lcd_command(uint8_t command)
{

}

void lcd_write(uint8_t* message)
{

}

void lcd_test()
{
	lcd_write("Hello World");
}
