/*
 * spi_test_prog.c
 *
 *  Created on: Mar 16, 2020
 *      Author: zac carico
 */


#include "spi_test_prog.h"

spi_dev fram_dev = {
		.spi = &riscv_spi,
		.spi_sel = SPI_SLAVE_0
};

spi_dev external_spi_0 = {
		.spi = &riscv_spi,
		.spi_sel = SPI_SLAVE_1
};

spi_dev external_spi_1 = {
		.spi = &riscv_spi,
		.spi_sel = SPI_SLAVE_2
};

spi_dev adc_dev = {
		.spi = &riscv_spi,
		.spi_sel = SPI_SLAVE_3
};

spi_dev lcd_screen_dev = {
		.spi = &riscv_spi,
		.spi_sel = SPI_SLAVE_4
};

spi_dev accelerometer_dev = {
		.spi = &riscv_spi,
		.spi_sel = SPI_SLAVE_5
};

void spi_test_init(void)
{
	quit_spi_test = 0;
	spi_command_byte = 0;
	selected_dev = &external_spi_0;
	selected_dev_id = external_spi_0.spi_sel;

	SPI_init(&riscv_spi, FLASH_CORE_SPI_BASE, 32);
	SPI_configure_master_mode(&riscv_spi);
}

void spi_test_read(spi_dev *device, uint8_t *command, uint8_t *data, uint8_t data_size)
{
	SPI_set_slave_select(device->spi, device->spi_sel);
	SPI_transfer_block(device->spi, command, 1, data, data_size);
	SPI_clear_slave_select(device->spi, device->spi_sel);
}

void spi_test_write(spi_dev *device, uint8_t *data, uint8_t data_size, uint8_t *resp_data)
{
	SPI_set_slave_select(device->spi, device->spi_sel);
	SPI_transfer_block(device->spi, data, data_size, resp_data, 1);
	SPI_clear_slave_select(device->spi, device->spi_sel);
}

void spi_test_handler(void)
{
	char command = 0;

	UART_polled_tx_string(&g_uart, (const uint8_t *)"\n\rWELCOME TO THE SPI TEST!\n\r");
	spi_test_display_commands();
	spi_test_init();

	while(quit_spi_test == 0)
	{
		UART_polled_tx_string(&g_uart, (const uint8_t *)"\n\r What would you like to do?\n\r");
		command = get_single_char_from_user();
		switch(command)
		{
			case 'h':
				spi_test_display_commands();
				break;
			case 'd':
				spi_test_display_devices();
				break;
			case 'q':
				quit_spi_test = 1;
				break;
			case '0':
				spi_test_change_selected_device();
				break;
			case '1':
				spi_test_display_selected_device();
				break;
			case '2':
				spi_test_send_write_command();
				break;
			case '3':
				spi_test_send_read_command();
				break;
			default:
				spi_test_display_incorrect_command();
				break;
		}
	}

	UART_polled_tx_string(&g_uart, (const uint8_t *)"\n\rLeaving SPI Test Program\n\r");
	return;
}

void spi_test_send_write_command(void)
{
	char command = 0;

	while(quit_spi_test == 0)
	{
		UART_polled_tx_string(&g_uart, (const uint8_t *)"You have entered the \"Send Write Command\" tool\n\r\n\r");
		spi_test_display_write_command_instructions();
		command = get_single_char_from_user();
		switch(command)
		{
			case 'h':
				spi_test_display_write_command_instructions();
				break;
			case 'd':
				spi_test_display_devices();
				break;
			case 'q':
				quit_spi_test = 1;
				break;
			case '0':
				spi_test_change_selected_device();
				break;
			case '1':
				spi_test_display_selected_device();
				break;
			case '2':
				spi_test_write_single_byte();
				break;
			case '3':
				spi_test_write_quad_byte();
				break;
			case '4':
				spi_test_write_custom_byte();
				break;
			default:
				spi_test_display_incorrect_command();
				break;
		}
	}

	quit_spi_test = 0;
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\n\rWELCOME TO THE SPI TEST!\n\r");
}

void spi_test_send_read_command(void)
{
	char command = 0;

	while(quit_spi_test == 0)
	{
		UART_polled_tx_string(&g_uart, (const uint8_t *)"You have entered the \"Send Write Command\" tool\n\r\n\r");
		spi_test_display_write_command_instructions();
		command = get_single_char_from_user();
		switch(command)
		{
			case 'h':
				spi_test_display_read_command_instructions();
				break;
			case 'd':
				spi_test_display_devices();
				break;
			case 'q':
				quit_spi_test = 1;
				break;
			case '0':
				spi_test_change_selected_device();
				break;
			case '1':
				spi_test_display_selected_device();
				break;
			case '2':
				spi_test_read_single_byte();
				break;
			case '3':
				spi_test_read_quad_byte();
				break;
			case '4':
				spi_test_read_custom_byte();
				break;
			default:
				spi_test_display_incorrect_command();
				break;
		}
	}

	quit_spi_test = 0;
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\n\rWELCOME TO THE SPI TEST!\n\r");
}

void spi_test_display_write_command_instructions(void)
{
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\tCOMMANDS:\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\t- 0\t change selected device\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\t- 1\t display selected device\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\t- 2\t write a single byte\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\t- 3\t write 4 bytes\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\t- 4\t write custom number of bytes\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\t- h\t display these commands\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\t- d\t display SPI device IDs\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\t- q\t exit \"Send Write Command\" tool\n\r");
}

void spi_test_write_single_byte(void)
{
	uint8_t writeData[1] = {0};
	uint8_t response = 0;
	uint8_t sendData = 0;
	char hexStr[5];

	UART_polled_tx_string(&g_uart, (const uint8_t *)"You have entered the \"Send Single Byte\" tool\n\r\n\r");

	while(sendData == 0)
	{
		UART_polled_tx_string(&g_uart, (const uint8_t *)"\tEnter Write Command:");
		spi_command_byte = (uint8_t)(get_bytes_from_user(1));

		UART_polled_tx_string(&g_uart, (const uint8_t *)"\tEnter Value to write:");
		writeData[0] = (uint8_t)(get_bytes_from_user(1));

		UART_polled_tx_string(&g_uart, (const uint8_t *)"\tSend write command \"");
		int_to_single_byte_string(spi_command_byte, hexStr);
		UART_polled_tx_string(&g_uart, (const uint8_t *)hexStr);
		UART_polled_tx_string(&g_uart, (const uint8_t *)"\" and value \"");
		int_to_single_byte_string(writeData[0], hexStr);
		UART_polled_tx_string(&g_uart, (const uint8_t *)hexStr);
		UART_polled_tx_string(&g_uart, (const uint8_t *)"\"?");
		if(get_yes_no_from_user() == 1)
			sendData = 1;
	}
	spi_test_write(selected_dev, writeData, 1, &response);

	UART_polled_tx_string(&g_uart, (const uint8_t *)"\n\r\tData has been sent!\n\r");

	UART_polled_tx_string(&g_uart, (const uint8_t *)"\tResponse was \"");
	int_to_single_byte_string(response, hexStr);
	UART_polled_tx_string(&g_uart, (const uint8_t *)hexStr);
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\"\n\r");
}

void spi_test_write_quad_byte(void)
{
	uint8_t i = 0;
	uint8_t response = 0;
	uint8_t sendData = 0;
	uint8_t temp[1] = {0};
	uint8_t writeData[4];
	char hexStr[5];

	UART_polled_tx_string(&g_uart, (const uint8_t *)"You have entered the \"Send Quad Byte\" tool\n\r\n\r");

	while(sendData == 0)
	{
		UART_polled_tx_string(&g_uart, (const uint8_t *)"\tEnter Write Command:");
		spi_command_byte = get_bytes_from_user(1);

		for(i = 0; i < 4; i++)
		{
			temp[0] = i + '0';
			UART_polled_tx_string(&g_uart, (const uint8_t *)"\tEnter Value for byte ");
			UART_polled_tx_string(&g_uart, (const uint8_t *)temp);
			if(i == 0)
				UART_polled_tx_string(&g_uart, (const uint8_t *)" (MSB)");
			UART_polled_tx_string(&g_uart, (const uint8_t *)":\n\r");
			writeData[i] = (uint8_t)(get_bytes_from_user(1));
		}


		UART_polled_tx_string(&g_uart, (const uint8_t *)"\tSend write command \"");
		int_to_single_byte_string(spi_command_byte, hexStr);
		UART_polled_tx_string(&g_uart, (const uint8_t *)hexStr);
		UART_polled_tx_string(&g_uart, (const uint8_t *)"\" and values");
		for(i = 0; i < 4; i++)
		{
			int_to_single_byte_string(writeData[i], hexStr);
			UART_polled_tx_string(&g_uart, (const uint8_t *)" \"");
			UART_polled_tx_string(&g_uart, (const uint8_t *)hexStr);
			UART_polled_tx_string(&g_uart, (const uint8_t *)"\"");
		}

		UART_polled_tx_string(&g_uart, (const uint8_t *)"?[Y/N] ");
		if(get_yes_no_from_user() == 1)
			sendData = 1;
	}

	spi_test_write(selected_dev, writeData, 4, &response);
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\n\r\tData has been sent!\n\r");

	UART_polled_tx_string(&g_uart, (const uint8_t *)"\tResponse was \"");
	int_to_single_byte_string(response, hexStr);
	UART_polled_tx_string(&g_uart, (const uint8_t *)hexStr);
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\"\n\r");
}

void spi_test_write_custom_byte(void)
{
	uint8_t i = 0;
	uint8_t numBytes = 0;
	uint8_t response = 0;
	uint8_t sendData = 0;
	uint8_t temp[1] = {0};
	uint8_t* writeData;
	char hexStr[5];

	UART_polled_tx_string(&g_uart, (const uint8_t *)"You have entered the \"Send Custom Byte\" tool\n\r\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t *)"How many bytes would you like to send?\n\r");
	numBytes = get_dec_from_user(3);
	writeData = malloc(sizeof(int8_t)*numBytes);

	while(sendData == 0)
	{
		UART_polled_tx_string(&g_uart, (const uint8_t *)"\tEnter Write Command:");
		spi_command_byte = get_bytes_from_user(1);

		for(i = 0; i < numBytes; i++)
		{
			temp[0] = i + '0';
			UART_polled_tx_string(&g_uart, (const uint8_t *)"\tEnter Value for byte ");
			UART_polled_tx_string(&g_uart, (const uint8_t *)temp);
			if(i == 0)
				UART_polled_tx_string(&g_uart, (const uint8_t *)" (MSB)");
			UART_polled_tx_string(&g_uart, (const uint8_t *)":\n\r");
			writeData[i] = (uint8_t)(get_bytes_from_user(1));
		}


		UART_polled_tx_string(&g_uart, (const uint8_t *)"\tSend write command \"");
		int_to_single_byte_string(spi_command_byte, hexStr);
		UART_polled_tx_string(&g_uart, (const uint8_t *)hexStr);
		UART_polled_tx_string(&g_uart, (const uint8_t *)"\" and values");
		for(i = 0; i < numBytes; i++)
		{
			int_to_single_byte_string(writeData[i], hexStr);
			UART_polled_tx_string(&g_uart, (const uint8_t *)" \"");
			UART_polled_tx_string(&g_uart, (const uint8_t *)hexStr);
			UART_polled_tx_string(&g_uart, (const uint8_t *)"\"");
		}

		UART_polled_tx_string(&g_uart, (const uint8_t *)"?[Y/N] ");
		if(get_yes_no_from_user() == 1)
			sendData = 1;
	}

	spi_test_write(selected_dev, writeData, numBytes, &response);
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\n\r\tData has been sent!\n\r");

	UART_polled_tx_string(&g_uart, (const uint8_t *)"\tResponse was \"");
	int_to_single_byte_string(response, hexStr);
	UART_polled_tx_string(&g_uart, (const uint8_t *)hexStr);
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\"\n\r");
	free(writeData);
}

void spi_test_display_read_command_instructions(void)
{
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\tCOMMANDS:\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\t- 0\t change selected device\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\t- 1\t display selected device\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\t- 2\t read a single byte\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\t- 3\t read 4 bytes\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\t- 4\t read custom number of bytes\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\t- h\t display these commands\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\t- d\t display SPI device IDs\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\t- q\t exit \"Send Write Command\" tool\n\r");
}

void spi_test_read_single_byte(void)
{
	uint8_t readData[1] = {0};
	uint8_t sendData = 0;
	char hexStr[5];

	UART_polled_tx_string(&g_uart, (const uint8_t *)"You have entered the \"Read Single Byte\" tool\n\r\n\r");

	while(sendData == 0)
	{
		UART_polled_tx_string(&g_uart, (const uint8_t *)"\tEnter Read Command:");
		spi_command_byte = (uint8_t)(get_bytes_from_user(1));

		UART_polled_tx_string(&g_uart, (const uint8_t *)"\tSend read command \"");
		int_to_single_byte_string(spi_command_byte, hexStr);
		UART_polled_tx_string(&g_uart, (const uint8_t *)hexStr);
		UART_polled_tx_string(&g_uart, (const uint8_t *)"\"?");
		if(get_yes_no_from_user() == 1)
			sendData = 1;
	}

	spi_test_read(selected_dev, &spi_command_byte, readData, 1);
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\n\r\tData has been read!\n\r");

	UART_polled_tx_string(&g_uart, (const uint8_t *)"\tRead Data is \"");
	int_to_single_byte_string(readData[0], hexStr);
	UART_polled_tx_string(&g_uart, (const uint8_t *)hexStr);
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\"\n\r");
}

void spi_test_read_quad_byte(void)
{
	uint8_t i = 0;
	uint8_t sendData = 0;
	uint8_t temp[1] = {0};
	uint8_t readData[4];
	char hexStr[5];

	UART_polled_tx_string(&g_uart, (const uint8_t *)"You have entered the \"Read Quad Byte\" tool\n\r\n\r");

	while(sendData == 0)
	{
		UART_polled_tx_string(&g_uart, (const uint8_t *)"\tEnter Read Command:");
		spi_command_byte = get_bytes_from_user(1);

		UART_polled_tx_string(&g_uart, (const uint8_t *)"\tSend write command \"");
		int_to_single_byte_string(spi_command_byte, hexStr);
		UART_polled_tx_string(&g_uart, (const uint8_t *)"\"?[Y/N] ");

		if(get_yes_no_from_user() == 1)
			sendData = 1;
	}

	spi_test_read(selected_dev, &spi_command_byte, readData, 4);
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\n\r\tData has been sent!\n\r");

	UART_polled_tx_string(&g_uart, (const uint8_t *)"\tRead Data is ");
	for(i = 0; i < 4; i++)
	{
		UART_polled_tx_string(&g_uart, (const uint8_t *)" \"");
		int_to_single_byte_string(readData[i], hexStr);
		UART_polled_tx_string(&g_uart, (const uint8_t *)hexStr);
		UART_polled_tx_string(&g_uart, (const uint8_t *)"\"");
	}

	UART_polled_tx_string(&g_uart, (const uint8_t *)"\n\r");
}

void spi_test_read_custom_byte(void)
{
	uint8_t i = 0;
	uint8_t numBytes = 0;
	uint8_t sendData = 0;
	uint8_t temp[1] = {0};
	uint8_t* readData;
	char hexStr[5];

	UART_polled_tx_string(&g_uart, (const uint8_t *)"You have entered the \"Send Custom Byte\" tool\n\r\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t *)"How many bytes would you like to send?\n\r");
	numBytes = get_dec_from_user(3);
	readData = malloc(sizeof(int8_t)*numBytes);

	while(sendData == 0)
	{
		UART_polled_tx_string(&g_uart, (const uint8_t *)"\tEnter Write Command:");
		spi_command_byte = get_bytes_from_user(1);

		UART_polled_tx_string(&g_uart, (const uint8_t *)"\tSend write command \"");
		int_to_single_byte_string(spi_command_byte, hexStr);
		UART_polled_tx_string(&g_uart, (const uint8_t *)hexStr);
		UART_polled_tx_string(&g_uart, (const uint8_t *)"\"?[Y/N] ");

		if(get_yes_no_from_user() == 1)
			sendData = 1;
	}

	spi_test_read(selected_dev, &spi_command_byte, readData, numBytes);
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\n\r\tData has been sent!\n\r");

	UART_polled_tx_string(&g_uart, (const uint8_t *)"\tRead Data is ");
	for(i = 0; i < 4; i++)
	{
		UART_polled_tx_string(&g_uart, (const uint8_t *)" \"");
		int_to_single_byte_string(readData[i], hexStr);
		UART_polled_tx_string(&g_uart, (const uint8_t *)hexStr);
		UART_polled_tx_string(&g_uart, (const uint8_t *)"\"");
	}

	UART_polled_tx_string(&g_uart, (const uint8_t *)"\n\r");
	free(readData);
}

void spi_test_display_commands(void)
{
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\tCOMMANDS:\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\t- 0\t change selected device\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\t- 1\t display selected device\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\t- 2\t send write command\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\t- 3\t send read command\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\t- h\t display these commands\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\t- d\t display SPI device IDs\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\t- q\t exit SPI Test Program\n\r");
}

void spi_test_display_devices(void)
{
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\tSPI DEVICE IDs:\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\t-(0) FRAM\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\t-(1) EXTERNAL_SPI_0\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\t-(2) EXTERNAL_SPI_1\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\t-(3) ADC\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\t-(4) LCD_SCREEN\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\t-(5) ACCELEROMETER\n\r");
}

void spi_test_display_selected_device(void)
{
	UART_polled_tx_string(&g_uart, (const uint8_t *)"\tCURRENT DEVICE: ");
	switch(selected_dev_id)
	{
		case FRAM:
			UART_polled_tx_string(&g_uart, (const uint8_t *)"FRAM\n\r");
			break;
		case EXTERNAL_SPI_0:
			UART_polled_tx_string(&g_uart, (const uint8_t *)"EXTERNAL_SPI_0\n\r");
			break;
		case EXTERNAL_SPI_1:
			UART_polled_tx_string(&g_uart, (const uint8_t *)"EXTERNAL_SPI_1\n\r");
			break;
		case ADC:
			UART_polled_tx_string(&g_uart, (const uint8_t *)"ADC\n\r");
			break;
		case LCD_SCREEN:
			UART_polled_tx_string(&g_uart, (const uint8_t *)"LCD_SCREEN\n\r");
			break;
		case ACCELEROMETER:
			UART_polled_tx_string(&g_uart, (const uint8_t *)"ACCELEROMETER\n\r");
			break;
		default:
			UART_polled_tx_string(&g_uart, (const uint8_t *)"<ERROR>\n\r");
			break;
	}
}

void spi_test_change_selected_device(void)
{
	uint8_t correct_id = 0;
	uint8_t isDeviceID = 0;

	UART_polled_tx_string(&g_uart, (const uint8_t *)"\n\rYou have entered the \"Change Selected Device\" tool\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t *)"- Enter device ID to set the new device\n\r");
	UART_polled_tx_string(&g_uart, (const uint8_t *)"- Enter \'d\' to display current selected device\n\r\n\r");

	spi_test_display_devices();
	while(correct_id == 0)
	{
		UART_polled_tx_string(&g_uart, (const uint8_t *)"Device ID:\n\r");
		char input = get_single_char_from_user();
		uint8_t device = (uint8_t)input - '0';

		switch(input)
		{
			case 'h':
				spi_test_display_devices();
				break;
			case 'd':
				spi_test_display_selected_device();
				break;
			case 'q':
				UART_polled_tx_string(&g_uart, (const uint8_t *)"Device not changed.\n\r");
				correct_id = 1;
				break;
			default:
				isDeviceID = 1;
				break;
		}

		if(isDeviceID)
		{
			correct_id = 1;
			switch(device)
			{
				case FRAM:
					UART_polled_tx_string(&g_uart, (const uint8_t *)"WARNING: This may not be a good idea...\n\r");
					selected_dev = &fram_dev;
					selected_dev_id = fram_dev.spi_sel;
					UART_polled_tx_string(&g_uart, (const uint8_t *)"FRAM selected\n\r");
					break;
				case EXTERNAL_SPI_0:
					selected_dev = &external_spi_0;
					selected_dev_id = external_spi_0.spi_sel;
					UART_polled_tx_string(&g_uart, (const uint8_t *)"EXTERNAL_SPI_0 selected\n\r");
					break;
				case EXTERNAL_SPI_1:
					selected_dev = &external_spi_1;
					selected_dev_id = external_spi_1.spi_sel;
					UART_polled_tx_string(&g_uart, (const uint8_t *)"EXTERNAL_SPI_1 selected\n\r");
					break;
				case ADC:
					selected_dev = &adc_dev;
					selected_dev_id = adc_dev.spi_sel;
					UART_polled_tx_string(&g_uart, (const uint8_t *)"ADC selected\n\r");
					break;
				case LCD_SCREEN:
					selected_dev = &lcd_screen_dev;
					selected_dev_id = lcd_screen_dev.spi_sel;
					UART_polled_tx_string(&g_uart, (const uint8_t *)"LCD_SCREEN selected\n\r");
					break;
				case ACCELEROMETER:
					selected_dev = &accelerometer_dev;
					selected_dev_id = accelerometer_dev.spi_sel;
					UART_polled_tx_string(&g_uart, (const uint8_t *)"ACCELEROMETER selected\n\r");
					break;
				default:
					UART_polled_tx_string(&g_uart, (const uint8_t *)"ERROR: Device not found!\n\r\n\r");
					correct_id = 0;
					isDeviceID = 0;
					break;
			}
		}
	}
}

void spi_test_display_incorrect_command(void)
{
	UART_polled_tx_string(&g_uart, (const uint8_t *)"ERROR! Invalid Command!\n\r");
}
