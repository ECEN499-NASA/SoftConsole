/**
 * @file    lcd_test.h
 * @author  Michael Ashford
 * @date    Apr 7, 2020
 *
 * @brief   Header file containing all the prototypes
 *          and declarations for the LCD test
 */

#ifndef LCD_TEST_H
#define LCD_TEST_H

/** @brief   gpio instance from main. LCD screen uses 28 thru 31 **/
extern gpio_instance_t g_gpio;


/** @brief   Initial setup of the LCD Screen */
void lcd_init(void);

/** @brief   Send a command to the LCD */
void lcd_command(uint8_t command);

/** @brief   Display a message on the LCD*/
void lcd_write(int message);

/** @brief   Display "Hello World" on the LCD */
void lcd_test(void);


#endif /*LCD_TEST_H*/
