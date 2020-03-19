#ifndef LCD_TEST_H
#define LCD_TEST_H


/*
 * Initialize the LCD screen. This should be called on FPGA startup.
 */
void lcd_init(void);

/*
 * Commands can be sent to the display
 */
void lcd_command(int command);

/*
 * Write a message to the screen
 */
void lcd_write(int message);

/*
 * Tests the LCD screen by displaying "Hello World"
 */
void lcd_test(void);


#endif /*LCD_TEST_H*/
