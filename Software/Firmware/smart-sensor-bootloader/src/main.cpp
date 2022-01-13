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
#include <stdio.h>
#include <list.h>
#include <Converter.h>
char offbuffer[2];
char hexbuffer[2];
char messagebuffer[500];
char input[2];
int hexno;
int bufferpos;
int state;
int timesincechar;
Node *proglist;

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
		// else if (messagebuffer[bufferpos] == 'H' & c != ':')
		else if (c != ':' & endmes == false)
		{
			// messagebuffer[bufferpos] = c;
			// bufferpos++;
			if (hexno == 0)
			{
				input[0] = c;
				hexno++;
			}
			else if (hexno == 1)
			{
				input[1] = c;
				hexno = 0;

				uint8_t inputval = convertHexToByte(&input[0], &input[1]);

				proglist = postInsert(proglist, inputval);
				input[0] = 0;
				input[1] = 0;
				unsigned char message[] = "Adding Nodes: ";
				int i = 0;
				while (message[i] != 0) /* print the String  "Character recieved: + The character" */
				{
					while (!(UCSR0A & (1 << UDRE)))
						;
					UDR0 = message[i];
					i++;
				}
				
				unsigned char testval[] = {(char)inputval};
				int b = 0;
				while (testval[b] != 0)
				{
					while (!(UCSR0A & (1 << UDRE)))
					{
						UDR0 = testval[b];
						b++;
					}
					
				}
				
				// while (!(UCSR0A & (1 << UDRE)))
				// {
				// 	UDR0 = proglist->n;
				// }
				// while (!(UCSR0A & (1 << UDRE)))
				// {
				// 	UDR0 = '\n\r';
				// }
			}
		}
		if (c == ':')
		{
			// int b = 0;
			// unsigned char filemes[] = "Contents of page ";
			// while (filemes[b] != 0)
			// {
			// 	while (!(UCSR0A & (1 << UDRE)))
			// 		;
			// 	{
			// 		UDR0 = filemes[b];
			// 		b++;
			// 	}
			// }

			// char pageno[4];
			// // snprintf(pageno, sizeof(pageno), "%d", page + 1);
			// int p = 0;
			// /* Send page number */
			// while (pageno[p] != 0)
			// {
			// 	while (!(UCSR0A & (1 << UDRE)))
			// 		;
			// 	{
			// 		UDR0 = pageno[p];
			// 		p++;
			// 	}
			// }
			// /* Send "space \n\r" Character */
			// while (!(UCSR0A & (1 << UDRE)))
			// 	;
			// UDR0 = ' \n\r';

			// for (int i = 0; i < sizeof(messagebuffer); i++)
			// {
			// 	if (messagebuffer[i] != 'H')
			// 	{
			// 		while (!(UCSR0A & (1 << UDRE)))
			// 			;
			// 		{
			// 			UDR0 = messagebuffer[i];
			// 		}
			// 		messagebuffer[i] = 'H';
			// 	}
			// }
			// while (!(UCSR0A & (1 << UDRE)))
			// 	;
			// UDR0 = ' \n\r';
			// bufferpos = 0;
			// // page++;
		}
		if (endmes == true)
		{
			// int d = 0;
			// unsigned char endfilemes[] = "Final page content: ";
			// while (endfilemes[d] != 0)
			// {
			// 	while (!(UCSR0A & (1 << UDRE)))
			// 		;
			// 	{
			// 		UDR0 = endfilemes[d];
			// 		d++;
			// 	}
			// }
			// while (!(UCSR0A & (1 << UDRE)))
			// 	;
			// UDR0 = ' \n\r';
			// for (int i = 0; i < sizeof(messagebuffer); i++)
			// {
			// 	while (!(UCSR0A & (1 << UDRE)))
			// 		;
			// 	{
			// 		if (messagebuffer[i] != 'H')
			// 		{
			// 			UDR0 = messagebuffer[i];
			// 		}
			// 	}
			// 	messagebuffer[i] = 'H';
			// }
			// while (!(UCSR0A & (1 << UDRE)))
			// 	;
			// UDR0 = ' \n\r';
			// state = 0;
			// // page = 0;
			// bufferpos = 0;
			// int d = 0;
			// unsigned char endfilemes[] = "Final page content: ";
			// while (endfilemes[d] != 0)
			// {
			// 	while (!(UCSR0A & (1 << UDRE)))
			// 	{
			// 		UDR0 = endfilemes[d];
			// 		d++;
			// 	}
			// }

			unsigned char message[] = "Printing Nodes: ";
			int i = 0;
			while (message[i] != 0) /* print the String  "Character recieved: + The character" */
			{
				while (!(UCSR0A & (1 << UDRE)))
					;
				UDR0 = message[i];
				i++;
			}

			for (size_t i = 0; i < countNodes(proglist); i++)
			{
				while (!(UCSR0A & (1 << UDRE)))
				{
					UDR0 = proglist->n;
					// UDR0 = countNodes(proglist);
					proglist = deleteNode(proglist, proglist->n);
				}
				while (!(UCSR0A & (1 << UDRE)))
					UDR0 = ' \n\r';
			}

			state = 0;

			// printList(proglist);
		}
	}

	if (state == 0)
	{
		if (offbuffer[0] == 'O')
		{
			if (c == 'F')
			{
				if (offbuffer[1] == 'F')
				{
					int i = 0;
					unsigned char shutdown[] = "Pretend this is a shutdown message. \n";
					while (shutdown[i] != 0)
					{
						while (!(UCSR0A & (1 << UDRE)))
							;
						{
							UDR0 = shutdown[i];
							i++;
						}
					}

					offbuffer[0] = 'P';
					offbuffer[1] = 'W';

					state = 2;
				}
				else
				{
					offbuffer[1] = c;
				}
			}
			else
			{
				offbuffer[0] = 'P';
				offbuffer[1] = 'W';
			}
		}
		else if (c == 'O')
		{
			offbuffer[0] = c;
		}

		if (hexbuffer[0] == 'H')
		{
			if (hexbuffer[1] == 'E')
			{
				if (c == 'X')
				{
					state = 1;
				}
				hexbuffer[0] = 'N';
				hexbuffer[1] = 'O';
			}
			else if (c == 'E')
			{
				hexbuffer[1] = c;
			}
			else
			{
				hexbuffer[0] = 'N';
				hexbuffer[1] = 'O';
			}
		}
		else if (c == 'H')
		{
			hexbuffer[0] = c;
		}

		unsigned char message[] = "Character recieved: ";
		int i = 0;
		while (message[i] != 0) /* print the String  "Character recieved: + The character" */
		{
			while (!(UCSR0A & (1 << UDRE)))
				;
			UDR0 = message[i];
			i++;
		}
		while (!(UCSR0A & (1 << UDRE)))
			;
		UDR0 = c;
		while (!(UCSR0A & (1 << UDRE)))
			;
		UDR0 = '\n\r';
	}
}

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

		// boot_page_fill(page + i, w);
	}

	boot_page_write(page); // Store buffer in flash page.
	boot_spm_busy_wait();  // Wait until the memory is written.

	// Reenable RWW-section again. We need this if we want to jump back
	// to the application after bootloading.

	boot_rww_enable();

	// Re-enable interrupts (if they were ever enabled).

	SREG = sreg;
}

int main(void)
{
	offbuffer[0] = 'P';
	offbuffer[1] = 'W';
	hexbuffer[0] = 'N';
	hexbuffer[1] = 'O';
	input[1] = '0';
	input[2] = '0';
	timesincechar = 0;
	hexno = 0;
	proglist = NULL;
	uint32_t baudrate = 9600;
	uint32_t ubrr = 20000000 / 16 / 9600 - 1; //((20000000 -((baudrate) * 8L)) / ((baudrate) * 16UL));

	UBRR0H = (unsigned char)(ubrr >> 8); // Configuration of the baudrate
	UBRR0L = (unsigned char)ubrr;
	UCSR0A = 0x00;
	UCSR0B = (1 << RXEN) | (1 << TXEN) | (1 << RXCIE);	 // Enable TX and RX and recieve interrupt
	UCSR0C = (1 << UCPOL) | (1 << UCSZ0) | (1 << UCSZ1); // 8 data and 1 stop
	sei();
	char data[] = "Hello from ATmega";
	int i = 0;

	for (int c = 0; c < sizeof(messagebuffer); c++)
	{
		messagebuffer[c] = 'H';
	}
	bufferpos = 0;
	state = 0;

	while (1) /* Loop the messsage continously */
	{
		if (state == 0)
		{
			i = 0;
			while (data[i] != 0) /* print the String  "Hello from ATmega" */
			{
				while (!(UCSR0A & (1 << UDRE)))
					;
				UDR0 = data[i];
				i++;
			}

			/* Send "\n" Character */
			while (!(UCSR0A & (1 << UDRE)))
				;
			UDR0 = '\n';

			/* Send "\r" Character */
			while (!(UCSR0A & (1 << UDRE)))
				;
			UDR0 = '\r';
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
			asm("JMP 0x3800");
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