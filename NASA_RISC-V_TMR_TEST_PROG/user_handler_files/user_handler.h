/**
 * @file	user_handler.h
 * @author	Zac Carico
 * @date	Mar 16 2020
 * 
 * @brief	Header file containing all the prototypes 
 * 			and declarations for handling user input
 */

#ifndef USER_HANDLER_H
#define USER_HANDLER_H

#include "core_uart_apb.h"

/**
 * @brief	ASCII values that can't be represented 
 * 			by characters well
 */
typedef enum {
	BACKSPACE_KEY = 0x08,
	TAB_HORZ_KEY = 0x09,
	NEW_LINE = 0x0A,
	TAB_VERT_KEY = 0x0B,
	RETURN_KEY = 0x0D,
	ESCAPE_KEY = 0x1B,
	SPACE_BAR = 0x20
} KEY_TABLE;

/**
 * @note	Global variable initialized in "main()"
 */
extern UART_instance_t g_uart;

/**
 * @note	Funciton prototypes 
 */
void user_handler_unit_test_handler(void);
void user_handler_invalid_command(void);
void user_handler_display_instructions(void);
void user_handler_test_yes_no(void);
void user_handler_test_string(void);
void user_handler_test_decimal(void);
void user_handler_test_bytes(void);
char get_single_char_from_user(void);
uint8_t get_yes_no_from_user(void);
void get_string_from_user(uint8_t numChars, uint8_t spaceEnabled, char* input);
uint32_t get_dec_from_user(uint8_t numDecPlaces);
uint32_t get_bytes_from_user(uint8_t numBytes);
void byte_to_dec_string(uint8_t byte, char dec_string[4]);
void int_to_hex_string(uint32_t num, char hex_string[12]);
void int_to_single_byte_string(uint8_t num, char hex_string[5]);


#endif /*USER_HANDLER_H*/
