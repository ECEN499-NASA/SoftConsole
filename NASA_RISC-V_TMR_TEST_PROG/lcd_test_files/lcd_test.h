#include "lcd_test.c"


/*
 * Initialize the LCD screen. This should be called on FPGA startup.
 */
void lcd_init();

/*
 * Commands can be sent to the display
 */
void lcd_command();

/*
 * Write a message to the screen
 */
void lcd_write();

/*
 * Tests the LCD screen by displaying "Hello World"
 */
void lcd_test();
