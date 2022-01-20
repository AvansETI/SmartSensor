/**
 * Entry point of the bootloader
 * @date   : 11 November 2021
 * @author : Tom Kaasenbrood
 * @version: 0.1 development version
 * #todo   : Implement bootloader
 * @updates
 */
#include <avr/boot.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <Converter.h>
char messagebuffer[50];
int bufferpos;
int state;
int timesincechar;
uint8_t prog[512];
int progpos;
char inputbuffer[50];
int inputpos;
char commandbuffer[3];

void boot_program_page(uint32_t page, uint8_t *buf)
{
	uint16_t i;
	uint8_t sreg;

	// Disable interrupts.

	sreg = SREG;
	cli();

	eeprom_busy_wait();

	boot_page_erase(page);
	boot_spm_busy_wait(); // Wait until the memory is erased.

	for (i = 0; i < SPM_PAGESIZE; i += 2)
	{
		// Set up little-endian word.

		uint16_t w = *buf++;
		w += (*buf++) << 8;

		boot_page_fill(page + i, w);
	}

	boot_page_write(page); // Store buffer in flash page.
	boot_spm_busy_wait();  // Wait until the memory is written.

	// Reenable RWW-section again. We need this if we want to jump back
	// to the application after bootloading.

	boot_rww_enable();

	// Re-enable interrupts (if they were ever enabled).

	SREG = sreg;
}

/* When a character is received on the serial bus, this interrupt is called. */
ISR(USART0_RX_vect)
{
	char c = UDR0;
	timesincechar = 0;
	/*For proper use of recieving hex file a delay should be added after every sent character to prevent data loss*/
	if (state == 1)
	{
		bool endmes = false;
		if (c == 'O')
		{
			endmes = true;
		}
		else if (c != ':' & c != '\n' & endmes == false)
		{
			//in current version if a single line is too long (should not happen with standard file generation)
			if (!(inputpos >= sizeof(inputbuffer)))
			{
				inputbuffer[inputpos] = c;
			}
			inputpos++;
		}
		if (c == '\n')
		{
			//due to hex file structure begin at position 8 with actually taking data and do not take the last few characters, these are for a better check but currently focused on functional
			inputpos = 8;
			while ((inputbuffer[inputpos] != 'Z') & !(inputpos >= (sizeof(inputbuffer) - 2)))
			{
				//convert to bytes and move by 2
				uint8_t progput = convertHexToByte(inputbuffer[inputpos], inputbuffer[inputpos + 1]);
				inputpos = inputpos + 2;
				//put converted bytes in array
				prog[progpos] = progput;
				progpos++;
			}
			inputpos = 0;
			for (int i = 0; i < sizeof(inputbuffer); i++)
			{
				inputbuffer[i] = 'Z';
			}
		}

		if (endmes == true)
		{
			//as a test print the prog array
			unsigned char progmessage[] = "Printing the prog array\n";
			int i = 0;
			while (progmessage[i] != 0)
			{
				while (!(UCSR0A & (1 << UDRE)))
					;
				UDR0 = progmessage[i];
				i++;
			}

			int b = 0;
			int c = 0;
			while (!(b >= progpos))
			{
				while (!(UCSR0A & (1 << UDRE)))
					;
				UDR0 = '0x';
				while (!(UCSR0A & (1 << UDRE)))
					;
				UDR0 = prog[b];
				while (!(UCSR0A & (1 << UDRE)))
					;
				UDR0 = ' ';
				b++;
				c++;
				if (c == 10)
				{
					while (!(UCSR0A & (1 << UDRE)))
						;
					UDR0 = '\n\r';
				}
			}

			//do check and program page
			boot_program_page(0, prog);
			state = 0;
		}
	}

	if (state == 0)
	{
		//in current version the character Z is used as a control character and thus cannot be used in commands or input files
		//The character P is used to print the current message
		//normal state for recieving commands is 0
		if (!(bufferpos >= sizeof(messagebuffer)) & c != 'P')
		{
			messagebuffer[bufferpos] = c;
			bufferpos++;
		}
		else if (c != 'P')
		{
			bufferpos = 0;
			for (int i = 0; i < sizeof(messagebuffer); i++)
			{
				messagebuffer[i] = 'Z';
			}
		}

		//command for moving to other program, state 2
		if (commandbuffer[0] == 'O')
		{
			//command for moving to other program
			if (c == 'F')
			{
				if (commandbuffer[1] == 'F')
				{
					int b = 0;
					unsigned char shutdown[] = "Pretend this is a shutdown message. \n";

					for (int i = 0; i < sizeof(commandbuffer); i++)
					{
						commandbuffer[i] = 'Z';
					}

					state = 2;
				}
				else
				{
					commandbuffer[1] = c;
				}
			}
			else
			{
				for (int i = 0; i < sizeof(commandbuffer); i++)
				{
					commandbuffer[i] = 'Z';
				}
			}
		}
		else if (c == 'O')
		{
			commandbuffer[0] = c;
		}

		//command to go into hex mode, hex mode is state 1
		if (commandbuffer[0] == 'H')
		{
			if (commandbuffer[1] == 'E')
			{
				if (c == 'X')
				{
					state = 1;
				}
				for (int i = 0; i < sizeof(commandbuffer); i++)
				{
					commandbuffer[i] = 'Z';
				}
			}
			else if (c == 'E')
			{
				commandbuffer[1] = c;
			}
			else
			{
				for (int i = 0; i < sizeof(commandbuffer); i++)
				{
					commandbuffer[i] = 'Z';
				}
			}
		}
		else if (c == 'H')
		{
			commandbuffer[0] = c;
		}

		//prints contents of messagebuffer, keeps a limited buffer to lower memory usage
		if (c == 'P')
		{
			int i = 0;
			// while (messagebuffer[i] != 'Z')
			// {
			// 	//wait until channel is free
			// 	while (!(UCSR0A & (1 << UDRE)))
			// 		;
			// 	//print char
			// 	UDR0 = messagebuffer[i];
			// 	i++;
			// }
			while (!(i >= progpos))
			{
				//wait until channel is free
				while (!(UCSR0A & (1 << UDRE)))
					;
				//print char
				UDR0 = prog[i];
				i++;
			}
			//wait until channel is free
			while (!(UCSR0A & (1 << UDRE)))
				;
			UDR0 = '\n\r';
			for (int i = 0; i < sizeof(messagebuffer); i++)
			{
				messagebuffer[i] = 'Z';
			}
			bufferpos = 0;
		}
	}
}

int main(void)
{
	timesincechar = 0;
	uint32_t baudrate = 9600;
	uint32_t ubrr = 20000000 / 16 / 9600 - 1; //((20000000 -((baudrate) * 8L)) / ((baudrate) * 16UL));

	UBRR0H = (unsigned char)(ubrr >> 8); // Configuration of the baudrate
	UBRR0L = (unsigned char)ubrr;
	UCSR0A = 0x00;
	UCSR0B = (1 << RXEN) | (1 << TXEN) | (1 << RXCIE);	 // Enable TX and RX and recieve interrupt
	UCSR0C = (1 << UCPOL) | (1 << UCSZ0) | (1 << UCSZ1); // 8 data and 1 stop
	sei();

	for (int b = 0; b < sizeof(messagebuffer); b++)
	{
		messagebuffer[b] = 'Z';
	}
	for (int b = 0; b < sizeof(commandbuffer); b++)
	{
		commandbuffer[b] = 'Z';
	}
	bufferpos = 0;
	inputpos = 0;
	progpos = 0;
	state = 0;

	while (1) /* Loop the messsage continously */
	{
		if (state == 0)
		{
		}
		else if (state == 2)
		{
			int i = 0;
			unsigned char shutdown[] = "Jumping to other program. \n";
			while (shutdown[i] != 0)
			{
				while (!(UCSR0A & (1 << UDRE)))
					;
				{
					UDR0 = shutdown[i];
					i++;
				}
			}
			asm("JMP 0x0000");
		}
		//end if timed out
		timesincechar++;
		if (timesincechar >= 250 & state == 1)
		{
			for (int i = 0; i < sizeof(messagebuffer); i++)
			{
				while (!(UCSR0A & (1 << UDRE)))
					;
				{
					if (messagebuffer[i] != 'H')
					{
						UDR0 = messagebuffer[i];
					}
				}
				messagebuffer[i] = 'H';
			}
			while (!(UCSR0A & (1 << UDRE)))
				;
			UDR0 = ' \n\r';
			state = 0;
			// page = 0;
			bufferpos = 0;
		}

		_delay_ms(100);
	}
}