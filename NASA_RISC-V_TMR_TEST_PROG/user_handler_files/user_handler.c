
#include "user_handler.h"

void user_handler_unit_test_handler(void)
{
	uint8_t quit = 0;
	char command = 0;

	UART_polled_tx_string(&g_uart, (const uint8_t *)"Welcome to user handler unit tester!\n\r");
	user_handler_display_instructions();

	while(quit == 0)
	{
		command = get_single_char_from_user();
		switch(command)
		{
			case '0':
				user_handler_test_yes_no();
				break;
			case '1':
				user_handler_test_string();
				break;
			case '2':
				user_handler_test_decimal();
				break;
			case '3':
				user_handler_test_bytes();
				break;
			case 'h':
				user_handler_display_instructions();
				break;
			case 'q':
				quit = 1;
				break;
			default:
				user_handler_invalid_command();
				break;
		}
	}
}

void user_handler_invalid_command(void)
{
	UART_polled_tx_string(&g_uart, (const uint8_t *)"ERROR: Invalid Command!\n\r");
}

void user_handler_display_instructions(void)
{
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\tCOMMANDS:\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\t-0 \t Test getting yes/no\n\r ");
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\t-1 \t Test getting entire string\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\t-2 \t Test getting decimal\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\t-3 \t Test getting bytes\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\t-h \t Display this menu\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\t-q \t Quit\n\r");
}

void user_handler_test_yes_no(void)
{
	UART_polled_tx_string(&g_uart, (const uint8_t *)"YES/NO:\n\r");
	if(get_yes_no_from_user())
		UART_polled_tx_string(&g_uart, (const uint8_t *)"TRUE\n\r");
	else
		UART_polled_tx_string(&g_uart, (const uint8_t *)"FALSE\n\r");
}

void user_handler_test_string(void)
{
	char str[50];
	UART_polled_tx_string(&g_uart, (const uint8_t *)"STRING TEST:\n\r");

	UART_polled_tx_string(&g_uart, (const uint8_t *)"\tNO-SPACES:\n\r");
	get_string_from_user(50, 0, str);
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\tYou Entered: ");
	UART_polled_tx_string(&g_uart, (const uint8_t *)str);

	UART_polled_tx_string(&g_uart, (const uint8_t *)"\n\r\n\r\tSPACES:\n\r");
	get_string_from_user(50, 1, str);
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\tYou Entered: ");
	UART_polled_tx_string(&g_uart, (const uint8_t *)str);
}

void user_handler_test_decimal(void)
{
	uint8_t num[1];
	char decStr[4];

	UART_polled_tx_string(&g_uart, (const uint8_t *)"DECIMAL TEST:\n\r");

	num[0] = (uint8_t)get_dec_from_user(3);
	byte_to_dec_string(num[0], decStr);

	UART_polled_tx_string(&g_uart, (const uint8_t *)"\tRAW VALUE: ");
	UART_polled_tx_string(&g_uart, (const uint8_t *)num);

	UART_polled_tx_string(&g_uart, (const uint8_t *)"\n\r\tSTRING VALUE:");
	UART_polled_tx_string(&g_uart, (const uint8_t *)decStr);
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\n\r");
}

void user_handler_test_bytes(void)
{
	uint32_t byteData[1];
	char hexStr[12];
	UART_polled_tx_string(&g_uart, (const uint8_t *)"BYTES TEST:\n\r");

	UART_polled_tx_string(&g_uart, (const uint8_t *)"\tSingle Byte:\n\r");
	byteData[0] = get_bytes_from_user(1);
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\t-RAW VALUE:");
	UART_polled_tx_string(&g_uart, (const uint8_t *)byteData);

	UART_polled_tx_string(&g_uart, (const uint8_t *)"\n\r\t-STRING VALUE:");
	int_to_hex_string(byteData[0], hexStr);
	UART_polled_tx_string(&g_uart, (const uint8_t *)hexStr);

	UART_polled_tx_string(&g_uart, (const uint8_t *)"\n\r\tQuad Byte:\n\r");
	byteData[0] = get_bytes_from_user(4);
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\t-RAW VALUE:");
	UART_polled_tx_string(&g_uart, (const uint8_t *)byteData);

	UART_polled_tx_string(&g_uart, (const uint8_t *)"\n\r\t-STRING VALUE:");
	int_to_hex_string(byteData[0], hexStr);
	UART_polled_tx_string(&g_uart, (const uint8_t *)hexStr);
}

char get_single_char_from_user(void)
{
	uint8_t rx_size=0;
	uint8_t rx_buff[2];
	uint8_t correct_input = 0;
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\n\r\t> ");

	while(correct_input == 0)
	{
		rx_size = UART_get_rx(&g_uart, rx_buff, sizeof(rx_buff));

		if(rx_size > 0)
			correct_input = 1;
	}
	rx_buff[1] = '\0';
	UART_polled_tx_string(&g_uart, (const uint8_t *)rx_buff);
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\n\r\n\r");
	return (char)rx_buff[0];
}

uint8_t get_yes_no_from_user(void)
{
	uint8_t rx_size=0;
	uint8_t rx_buff[2];
	uint8_t correct_input = 0;
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\n\r\t> ");

	while(correct_input == 0)
	{
		rx_size = UART_get_rx(&g_uart, rx_buff, sizeof(rx_buff));

		if(rx_size > 0)
			correct_input = 1;
	}

	rx_buff[1] = '\0';
	UART_polled_tx_string(&g_uart, (const uint8_t *)rx_buff);
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\n\r\n\r");

	if(rx_buff[0] == 'N' || rx_buff[0] == 'n')
		return 0;
	else
		return 1;
}

void get_string_from_user(uint8_t numChars, uint8_t spaceEnabled, char* input)
{
	uint8_t count = 0;
	uint8_t receivedInput = 0;
	uint8_t enteredValue = 0;
	uint8_t rx_size = 0;
	uint8_t rx_buf[2];
	char numCharsString[4];

	byte_to_dec_string(numChars, numCharsString);

	UART_polled_tx_string(&g_uart, (const uint8_t *)"\n\r\tPlease enter no more than ");
	UART_polled_tx_string(&g_uart, (const uint8_t *)numCharsString);
	UART_polled_tx_string(&g_uart, (const uint8_t *)" characters:\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\t> ");

	while(receivedInput == 0)
	{
		while(enteredValue == 0)
		{
			rx_size = UART_get_rx(&g_uart, rx_buf, sizeof(rx_buf));
			if(rx_size > 0)
				enteredValue = 1;
		}
		rx_buf[1] = '\0';
		enteredValue = 0;

		if(count < numChars - 1)
		{
			switch(rx_buf[0])
			{
				case RETURN_KEY:
				case NEW_LINE:
					UART_polled_tx_string(&g_uart, (const uint8_t *)"\n\r");
					receivedInput = 1;
					break;
				case BACKSPACE_KEY:
				case TAB_HORZ_KEY:
				case ESCAPE_KEY:
					break;
				case SPACE_BAR:
					if(spaceEnabled)
					{
						UART_polled_tx_string(&g_uart, (const uint8_t *)rx_buf);
						input[count] = ' ';
						count++;
					}
					break;
				default: // assume user entered character
					UART_polled_tx_string(&g_uart, (const uint8_t *)rx_buf);
					input[count] = (char)rx_buf[0];
					count++;
					break;
			}
		}
		enteredValue = 0;
	}
	input[count] = '\0';
}

uint32_t get_dec_from_user(uint8_t numDecPlaces)
{
	uint32_t input = 0;
	uint8_t count = 0;
	uint32_t placeHolder = 1;
	uint8_t receivedInput = 0;
	uint8_t enteredValue = 0;
	uint8_t rx_size = 0;
	uint8_t rx_buf[2];

	UART_polled_tx_string(&g_uart, (const uint8_t *)"\t> ");

	while(receivedInput == 0)
	{
		while(enteredValue == 0)
		{
			rx_size = UART_get_rx(&g_uart, rx_buf, sizeof(rx_buf));
			if(rx_size > 0)
				enteredValue = 1;
		}
		rx_buf[1] = '\0';
		enteredValue = 0;

		if(count < numDecPlaces)
		{
			switch(rx_buf[0])
			{
				case RETURN_KEY:
				case NEW_LINE:
					UART_polled_tx_string(&g_uart, (const uint8_t *)"\n\r");
					receivedInput = 1;
					break;
				case BACKSPACE_KEY:
				case TAB_HORZ_KEY:
				case ESCAPE_KEY:
				case SPACE_BAR:
					break;
				default:
					if(rx_buf[0] >= '0' && rx_buf[0] <= '9') //Look only for numbers
					{
						UART_polled_tx_string(&g_uart, (const uint8_t *)rx_buf);
						input += (rx_buf[0] - '0') * placeHolder;
						count++;
						placeHolder *= 10;
					}
					break;
			}
		}
		else if(rx_buf[0] == RETURN_KEY || rx_buf[0] == NEW_LINE)
		{
			UART_polled_tx_string(&g_uart, (const uint8_t *)"\n\r");
			receivedInput = 1;
		}
	}

	return input;
}

uint32_t get_bytes_from_user(uint8_t numBytes)
{
	uint32_t input = 0;
	uint8_t enteredValue = 0;
	uint8_t userFinished = 0;
	uint8_t rx_size = 0;
	uint16_t numPlaces = numBytes * 2;
	uint8_t rx_buf[2] = {0};
	char numByteStr[4];

	byte_to_dec_string(numBytes, numByteStr);

	UART_polled_tx_string(&g_uart, (const uint8_t *)"\n\r\n\r\tEnter up to ");
	UART_polled_tx_string(&g_uart, (const uint8_t *)numByteStr);
	UART_polled_tx_string(&g_uart, (const uint8_t *)" bytes with the first entry being the MSB.\n\r\tSpaces can be used as separators.\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\t> 0x");

	while(userFinished == 0)
	{

		while(enteredValue == 0)
		{
			rx_size = UART_get_rx(&g_uart, rx_buf, sizeof(rx_buf));
			if(rx_size > 0)
				enteredValue = 1;
		}
		rx_buf[1] = '\0';
		enteredValue = 0;

		if((rx_buf[0] >= '0' && rx_buf[0] <= '9') ||
		   (rx_buf[0] >= 'a' && rx_buf[0] <= 'f') ||
		   (rx_buf[0] >= 'A' && rx_buf[0] <= 'F'))
			UART_polled_tx_string(&g_uart, (const uint8_t *)rx_buf);
		else if(rx_buf[0] == SPACE_BAR)
			UART_polled_tx_string(&g_uart, (const uint8_t *)" ");
		else if(rx_buf[0] == RETURN_KEY)
			UART_polled_tx_string(&g_uart, (const uint8_t *)"\n\r");

		switch(rx_buf[0])
		{
			case RETURN_KEY:
			case NEW_LINE:
				return input;
				break;
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				input = input << 4;
				input += rx_buf[0] - '0';
				break;
			case 'a':
			case 'A':
				input = input << 4;
				input += 0x0A;
				break;
			case 'b':
			case 'B':
				input = input << 4;
				input += 0x0B;
				break;
			case 'c':
			case 'C':
				input = input << 4;
				input += 0x0C;
				break;
			case 'd':
			case 'D':
				input = input << 4;
				input += 0x0D;
				break;
			case 'e':
			case 'E':
				input = input << 4;
				input += 0x0E;
				break;
			case 'f':
			case 'F':
				input = input << 4;
				input += 0x0F;
				break;
			default:
				break;
		}
	}

	return input;
}

void byte_to_dec_string(uint8_t byte, char dec_string[4])
{
	dec_string[3] = '\0';
	dec_string[2] = byte % 10 + '0';
	dec_string[1] = byte / 10 % 10 + '0';
	dec_string[0] = byte / 100 % 10 + '0';
}

void int_to_hex_string(uint32_t num, char hex_string[12])
{
	hex_string[11] = '\0';
	hex_string[10] = num % 0x10 + '0';
	hex_string[9] = num / 0x10 % 0x10 + '0';
	hex_string[8] = num / 0x100 % 0x10 + '0';
	hex_string[7] = num / 0x1000 % 0x10 + '0';
	hex_string[6] = num / 0x10000 % 0x10 + '0';
	hex_string[5] = num / 0x100000 % 0x10 + '0';
	hex_string[4] = num / 0x1000000 % 0x10 + '0';
	hex_string[3] = num / 0x10000000 % 0x10 + '0';
	hex_string[2] = num / 0x100000000 % 0x10 + '0';
	hex_string[1] = 'x';
	hex_string[0] = '0';
}

void int_to_single_byte_string(uint8_t num, char hex_string[5])
{
	hex_string[4] = '\0';
	hex_string[3] = num % 0x10 + '0';
	hex_string[2] = num / 0x10 % 0x10 + '0';
	hex_string[1] = 'x';
	hex_string[0] = '0';
}
