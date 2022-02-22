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
#include <Serial.h>
#include <stdio.h>
#include <StateMachine.h>
// char messagebuffer[50];
// int bufferpos;
// int state;
// int timesincechar;
// uint8_t prog[1024];
// int progpos;
// char inputbuffer[50];
// int inputpos;
// char commandbuffer[3];
// uint32_t pageno;

// void boot_program_page(uint32_t page, uint8_t *buf)
// {
// 	uint16_t i;
// 	uint8_t sreg;

// 	// Disable interrupts.

// 	sreg = SREG;
// 	cli();

// 	eeprom_busy_wait();

// 	boot_page_erase(page);
// 	boot_spm_busy_wait(); // Wait until the memory is erased.

// 	for (i = 0; i < SPM_PAGESIZE; i += 2)
// 	{
// 		// Set up little-endian word.

// 		uint16_t w = *buf++;
// 		w += (*buf++) << 8;

// 		boot_page_fill(page + i, w);
// 	}

// 	boot_page_write(page); // Store buffer in flash page.
// 	boot_spm_busy_wait();  // Wait until the memory is written.

// 	// Reenable RWW-section again. We need this if we want to jump back
// 	// to the application after bootloading.

// 	boot_rww_enable();

// 	// Re-enable interrupts (if they were ever enabled).

// 	SREG = sreg;
// }

// void USART_Transmit( unsigned char data )
// {
//  /* Wait for empty transmit buffer */
//  while ( !( UCSR0A & (1<<UDRE)) )
//  ;
//  /* Put data into buffer, sends the data */
//  UDR0 = data;
// }

// /* When a character is received on the serial bus, this interrupt is called. */
// ISR(USART0_RX_vect)
// {
// 	char c = UDR0;
// 	timesincechar = 0;
// 	/*For proper use of recieving hex file a delay should be added after every sent character to prevent data loss*/
// 	if (state == 1)
// 	{
// 		bool endmes = false;
// 		if (c == 'O')
// 		{
// 			endmes = true;
// 		}
// 		else if (c != ':' & c != '\n' & endmes == false)
// 		{
// 			//in current version if a single line is too long (should not happen with standard file generation) then it is not properly input
// 			if (!(inputpos >= sizeof(inputbuffer)))
// 			{
// 				inputbuffer[inputpos] = c;
// 			}
// 			inputpos++;
// 		}
// 		if (c == '\n')
// 		{
// 			//due to hex file structure begin at position 8 with actually taking data and do not take the last few characters, these are for a better check but currently focused on functional
// 			inputpos = 8;
// 			while ((inputbuffer[inputpos] != 'Z') & !(inputpos >= (sizeof(inputbuffer) - 2)))
// 			{
// 				//convert to bytes and move by 2
// 				uint8_t progput = convertHexToByte(inputbuffer[inputpos], inputbuffer[inputpos + 1]);
// 				// while (!(UCSR0A & (1 << UDRE)))
// 				// 	;
// 				// UDR0 = inputbuffer[inputpos];
// 				// UDR0 = inputbuffer[inputpos+1];
// 				// USART_Transmit(progput);

// 				inputpos = inputpos + 2;
// 				//put converted bytes in array
// 				prog[progpos] = progput;
// 				USART_Transmit(prog[progpos]);

// 				progpos++;
// 				// if (progpos >= 128)
// 				// {
// 				// 	boot_program_page(pageno * SPM_PAGESIZE, prog);
// 				// 	pageno++;
// 				// 	progpos = 0;
// 				// }
// 			}
// 			inputpos = 0;
// 			for (int i = 0; i < sizeof(inputbuffer); i++)
// 			{
// 				inputbuffer[i] = 'Z';
// 			}
// 		}

// 		if (endmes == true)
// 		{
// 			// //as a test print the prog array
// 			// unsigned char progmessage[] = "Printing the prog array\n";
// 			// int i = 0;
// 			// while (progmessage[i] != 0)
// 			// {
// 			// 	while (!(UCSR0A & (1 << UDRE)))
// 			// 		;
// 			// 	UDR0 = progmessage[i];
// 			// 	i++;
// 			// }

// 			// int b = 0;
// 			// int d = 0;
// 			// while (!(b >= sizeof(prog)))
// 			// {
// 			// 	while (!(UCSR0A & (1 << UDRE)))
// 			// 		;
// 			// 	UDR0 = '0x';
// 			// 	while (!(UCSR0A & (1 << UDRE)))
// 			// 		;
// 			// 	UDR0 = prog[b];
// 			// 	while (!(UCSR0A & (1 << UDRE)))
// 			// 		;
// 			// 	UDR0 = ' ';
// 			// 	b++;
// 			// 	d++;
// 			// 	if (d == 10)
// 			// 	{
// 			// 		while (!(UCSR0A & (1 << UDRE)))
// 			// 			;
// 			// 		UDR0 = '\n\r';
// 			// 		d = 0;
// 			// 	}
// 			// }

// 			//do check and program page
// 			//earlier attempt
// 			// boot_program_page(pageno * SPM_PAGESIZE, prog);

// 			//hopefully this works
// 			uint8_t *prog_ptr = prog;
// 			for (int i = 0; i < 5; i++)
// 			{
// 				USART_Transmit(prog[i]);
// 			}

// 			for (int i = 0; i < 8; i++)
// 			{
// 				boot_program_page(pageno, prog_ptr);
// 				pageno += SPM_PAGESIZE;
// 				prog_ptr += SPM_PAGESIZE;
// 			}

// 			asm("jmp 0");

// 			//state back to 0
// 			state = 0;
// 		}
// 	}

// 	if (state == 0)
// 	{
// 		//in current version the character Z is used as a control character and thus cannot be used in commands or input files
// 		//The character P is used to print the current message
// 		//normal state for recieving commands is 0
// 		if (!(bufferpos >= sizeof(messagebuffer)) & c != 'P')
// 		{
// 			messagebuffer[bufferpos] = c;
// 			bufferpos++;
// 		}
// 		else if (c != 'P')
// 		{
// 			bufferpos = 0;
// 			for (int i = 0; i < sizeof(messagebuffer); i++)
// 			{
// 				messagebuffer[i] = 'Z';
// 			}
// 		}

// 		//command for moving to other program, state 2
// 		if (commandbuffer[0] == 'O')
// 		{
// 			//command for moving to other program
// 			if (c == 'F')
// 			{
// 				if (commandbuffer[1] == 'F')
// 				{
// 					for (int i = 0; i < sizeof(commandbuffer); i++)
// 					{
// 						commandbuffer[i] = 'Z';
// 					}

// 					state = 2;
// 				}
// 				else
// 				{
// 					commandbuffer[1] = c;
// 				}
// 			}
// 			else
// 			{
// 				for (int i = 0; i < sizeof(commandbuffer); i++)
// 				{
// 					commandbuffer[i] = 'Z';
// 				}
// 			}
// 		}
// 		else if (c == 'O')
// 		{
// 			commandbuffer[0] = c;
// 		}

// 		//command to go into hex mode, hex mode is state 1
// 		if (commandbuffer[0] == 'H')
// 		{
// 			if (commandbuffer[1] == 'E')
// 			{
// 				if (c == 'X')
// 				{
// 					state = 1;
// 				}
// 				for (int i = 0; i < sizeof(commandbuffer); i++)
// 				{
// 					commandbuffer[i] = 'Z';
// 				}
// 			}
// 			else if (c == 'E')
// 			{
// 				commandbuffer[1] = c;
// 			}
// 			else
// 			{
// 				for (int i = 0; i < sizeof(commandbuffer); i++)
// 				{
// 					commandbuffer[i] = 'Z';
// 				}
// 			}
// 		}
// 		else if (c == 'H')
// 		{
// 			commandbuffer[0] = c;
// 		}

// 		//prints contents of messagebuffer, keeps a limited buffer to lower memory usage
// 		if (c == 'P')
// 		{
// 			int i = 0;
// 			while (messagebuffer[i] != 'Z')
// 			{
// 				//wait until channel is free
// 				while (!(UCSR0A & (1 << UDRE)))
// 					;
// 				//print char
// 				UDR0 = messagebuffer[i];
// 				i++;
// 			}
// 			//wait until channel is free
// 			while (!(UCSR0A & (1 << UDRE)))
// 				;
// 			UDR0 = '\n\r';
// 			for (int i = 0; i < sizeof(messagebuffer); i++)
// 			{
// 				messagebuffer[i] = 'Z';
// 			}
// 			bufferpos = 0;
// 		}
// 	}
// }

// int main(void)
// {

// 	timesincechar = 0;
// uint32_t baudrate = 9600;
// uint32_t ubrr = 20000000 / 16 / 9600 - 1;
// // uint32_t ubrr = ((20000000 -((baudrate) * 8L)) / ((baudrate) * 16UL));
// pageno = 0;

// UBRR0H = (unsigned char)(ubrr >> 8); // Configuration of the baudrate
// UBRR0L = (unsigned char)ubrr;
// UCSR0A = 0x00;
// UCSR0B = (1 << RXEN) | (1 << TXEN) | (1 << RXCIE);	 // Enable TX and RX and recieve interrupt
// UCSR0C = (1 << UCPOL) | (1 << UCSZ0) | (1 << UCSZ1); // 8 data and 1 stop
// sei();

// 	for (int b = 0; b < sizeof(messagebuffer); b++)
// 	{
// 		messagebuffer[b] = 'Z';
// 	}
// 	for (int b = 0; b < sizeof(commandbuffer); b++)
// 	{
// 		commandbuffer[b] = 'Z';
// 	}
// 	for (int b = 0; b < sizeof(prog); b++)
// 	{
// 		prog[b] = 0xFF;
// 	}

// 	bufferpos = 0;
// 	inputpos = 0;
// 	progpos = 0;
// 	state = 0;

// 	while (1) /* Loop the messsage continously */
// 	{
// 		if (state == 0)
// 		{
// 		}
// 		else if (state == 2)
// 		{
// 			int i = 0;
// 			unsigned char shutdown[] = "Jumping to other program. \n";
// 			while (shutdown[i] != 0)
// 			{
// 				while (!(UCSR0A & (1 << UDRE)))
// 					;
// 				{
// 					UDR0 = shutdown[i];
// 					i++;
// 				}
// 			}
// 			asm("jmp 0");
// 		}
// 		//end if timed out
// 		timesincechar++;
// 		if (timesincechar >= 250 & state == 1)
// 		{
// 			for (int i = 0; i < sizeof(messagebuffer); i++)
// 			{
// 				while (!(UCSR0A & (1 << UDRE)))
// 					;
// 				{
// 					if (messagebuffer[i] != 'H')
// 					{
// 						UDR0 = messagebuffer[i];
// 					}
// 				}
// 				messagebuffer[i] = 'H';
// 			}
// 			while (!(UCSR0A & (1 << UDRE)))
// 				;
// 			UDR0 = ' \n\r';
// 			state = 0;
// 			// page = 0;
// 			bufferpos = 0;
// 		}

// 		_delay_ms(100);
// 	}
// }

typedef enum
{
	bootState,
	recieveState,
	writeState,
	executeState,
	totalState
} states;

typedef enum
{
	bootEvent,
	recieveEvent,
	writeEvent,
	executeEvent,
	startEvent,
	totalEvent
} events;

STATE stateMachine(totalState, totalEvent);

// handlers for various events
//raiseevents in the handlers were are there for testing and are currently commented out
//events should be raised by other methods, not these events themselves
void bootHandler()
{
	char bootmes[] = "Boot\n";
	sendString(bootmes);
	// stateMachine.raiseEvent(bootEvent);
}
void recieveHandler()
{
	char recmes[] = "Recieve\n";
	sendString(recmes);
	// stateMachine.raiseEvent(recieveEvent);
}
void writeHandler()
{
	char wrimes[] = "Write\n";
	sendString(wrimes);
	// stateMachine.raiseEvent(writeEvent);
}
void executeHandler()
{
	char exemes[] = "Execute\n";
	sendString(exemes);
	// stateMachine.raiseEvent(executeEvent);
}

int main(void)
{

	DDRD |= 1 << PD4;
	PORTD |= 1 << PD4;
	_delay_ms(100);
	PORTD &= ~(1 << PD4);
	_delay_ms(1000);
	initSerial();
	char message[] = "Hello from Serial\n";
	int testint = 0;

	// add necessary data to state machine
	// add states to machine
	stateMachine.addState(bootState, bootHandler);
	stateMachine.addState(recieveState, recieveHandler);
	stateMachine.addState(writeState, writeHandler);
	stateMachine.addState(executeState, executeHandler);

	// add transitions to machine
	stateMachine.addTransition(bootState, bootEvent, recieveState);
	stateMachine.addTransition(recieveState, recieveEvent, writeState);
	stateMachine.addTransition(writeState, writeEvent, executeState);
	stateMachine.addTransition(executeState, executeEvent, bootState);

	// setup state machine
	stateMachine.setup(bootState, startEvent);
	while (1)
	{
		
		// sendString(message);
		testint++;
		if (testint == 1)
		{
			// simulating event to change state, will be worked on further
			// for now just test cycling through states with some testing of errors
			stateMachine.raiseEvent(bootEvent);
			sendString("yes");
		}
		else if (testint == 2)
		{
			stateMachine.raiseEvent(recieveEvent);
			sendString("yes");
		}
		else if (testint == 3)
		{
			stateMachine.raiseEvent(writeEvent);
			sendString("yes");
		}
		else if (testint == 4)
		{
			stateMachine.raiseEvent(executeEvent);
			sendString("yes");
		}
		else if (testint == 5)
		{
			stateMachine.raiseEvent(writeEvent);
			sendString("no");
		}
		else if (testint == 6)
		{
			stateMachine.raiseEvent(recieveEvent);
			sendString("no");
			testint = 0;
		}
		stateMachine.loop();


		_delay_ms(1000);
	}
}