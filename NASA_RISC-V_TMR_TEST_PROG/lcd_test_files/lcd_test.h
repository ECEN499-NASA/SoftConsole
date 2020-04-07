#ifndef LCD_TEST_H
#define LCD_TEST_H


/** @brief   Initial setup of the LCD Screen */
void lcd_init(void);

/** @brief   Send a command to the LCD */
void lcd_command(int command);

/** @brief   Display a message on the LCD*/
void lcd_write(int message);

/** @brief   Display "Hello World" on the LCD */
void lcd_test(void);


#endif /*LCD_TEST_H*/
