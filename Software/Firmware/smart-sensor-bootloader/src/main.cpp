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

static const char FIRMWARE_VERSION[] PROGMEM = "v1.0";

#define BAUD_RATE_9600_BPS  71  // 9600bps

// uint8_t prog[] = {
// 		0x0C,0x94,0x46,0x00,0x0C,0x94,0x50,0x00,0x0C,0x94,0x50,0x00,0x0C,0x94,0x50,0x00, // 16 bytes
// 		0x0C,0x94,0x50,0x00,0x0C,0x94,0x50,0x00,0x0C,0x94,0x50,0x00,0x0C,0x94,0x50,0x00,
// 		0x0C,0x94,0x50,0x00,0x0C,0x94,0x50,0x00,0x0C,0x94,0x50,0x00,0x0C,0x94,0x50,0x00,
// 		0x0C,0x94,0x50,0x00,0x0C,0x94,0x50,0x00,0x0C,0x94,0x50,0x00,0x0C,0x94,0x50,0x00,
// 		0x0C,0x94,0x50,0x00,0x0C,0x94,0x50,0x00,0x0C,0x94,0x50,0x00,0x0C,0x94,0x50,0x00,
// 		0x0C,0x94,0x50,0x00,0x0C,0x94,0x50,0x00,0x0C,0x94,0x50,0x00,0x0C,0x94,0x50,0x00,
// 		0x0C,0x94,0x50,0x00,0x0C,0x94,0x50,0x00,0x0C,0x94,0x50,0x00,0x0C,0x94,0x50,0x00,
// 		0x0C,0x94,0x50,0x00,0x0C,0x94,0x50,0x00,0x0C,0x94,0x50,0x00,0x0C,0x94,0x50,0x00, //128

// 		0x0C,0x94,0x50,0x00,0x0C,0x94,0x50,0x00,0x0C,0x94,0x50,0x00,0x11,0x24,0x1F,0xBE,
// 		0xCF,0xEF,0xD0,0xE4,0xDE,0xBF,0xCD,0xBF,0x0E,0x94,0x52,0x00,0x0C,0x94,0x65,0x00,
// 		0x0C,0x94,0x00,0x00,0x54,0x9A,0x5C,0x9A,0x8F,0xE0,0x97,0xE2,0x01,0x97,0xF1,0xF7,
// 		0x00,0xC0,0x00,0x00,0x5C,0x98,0x9F,0xEF,0x29,0xE6,0x88,0xE1,0x91,0x50,0x20,0x40,
// 		0x80,0x40,0xE1,0xF7,0x00,0xC0,0x00,0x00,0xEE,0xCF,0xF8,0x94,0xFF,0xCF,0xFF,0xFF,
// 		0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
// 		0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
// 		0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
// };

// void boot_program_page (uint32_t page, uint8_t *buf)
// {
// 	uint16_t i;
// 	uint8_t sreg;

// 	// Disable interrupts.

// 	sreg = SREG;
// 	cli();

// 	eeprom_busy_wait ();

// 	boot_page_erase (page);
// 	boot_spm_busy_wait ();      // Wait until the memory is erased.

// 	for (i=0; i<SPM_PAGESIZE; i+=2)
// 	{
// 		// Set up little-endian word.

// 		uint16_t w = *buf++;
// 		w += (*buf++) << 8;

// 		boot_page_fill (page + i, w);
// 	}

// 	boot_page_write (page);     // Store buffer in flash page.
// 	boot_spm_busy_wait();       // Wait until the memory is written.

// 	// Reenable RWW-section again. We need this if we want to jump back
// 	// to the application after bootloading.

// 	boot_rww_enable ();

// 	// Re-enable interrupts (if they were ever enabled).

// 	SREG = sreg;
// }
uint8_t busy = false;
uint8_t pointer = 0;
char buffer[30];
char offbuffer[2];

/* When a character is received on the serial bus, this interrupt is called. */
ISR(USART1_RX_vect) {
    char c = UDR1;
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
					while (!(UCSR1A & (1<<UDRE)));
					{
						UDR1 = shutdown[i];
						i++;
					}
					
				}
				
				offbuffer[0] = 'P';
				offbuffer[1] = 'W';
			} else {
				offbuffer[1] = c;
			}
			
		}
		
	} else if (c == 'O')
	{
		offbuffer[0] = c;
	}
	
	
	
	unsigned char message[] = "Character recieved: ";
	int i = 0;
		while(message[i] != 0) /* print the String  "Character recieved: + The character" */
		{
			while (!( UCSR1A & (1<<UDRE)));
				UDR1 = message[i];
				i++;
		}
		while (!( UCSR1A & (1<<UDRE)));
				UDR1 = c;
		while (!( UCSR1A & (1<<UDRE)));
				UDR1 = '\n\r';
}


void transmitChar(char data) {
    while ( !( UCSR1A & (1<<UDRE)) ); // Wait for empty transmit buffer
    UDR1 = data;
}

uint8_t print(const char* message) {
    if ( !busy ) {
        while (*message) {
            transmitChar(*message++);
        }
        return 0;
    }

    return 1;
}

uint8_t print_P(const char* message) {
    if ( !busy ) {
        while(pgm_read_byte(message) != 0x00) {
        	transmitChar(pgm_read_byte(message++));
        }

        return 0;
    }

    return 1; // Serial port is busy
}

int main(void) {
	// // long beep in bootloader
	// DDRD |= 1 << PD4;
	// PORTD |= 1 << PD4;
	// _delay_ms(100);
	// PORTD &= ~(1 << PD4);
	// _delay_ms(1000);

	// //start at flash_start = 0x0000
	// boot_program_page( 0, prog);

	// //start the actual program
	// asm("jmp 0");

	// // bootloader ends here

	//test for serial communication
	offbuffer[0] = 'P';
	offbuffer[1] = 'W';
	uint32_t baudrate = 9600;
    uint32_t ubrr = 20000000 / 16 / 9600-1;//((20000000 -((baudrate) * 8L)) / ((baudrate) * 16UL));

    UBRR1H = (unsigned char) (ubrr >> 8); // Configuration of the baudrate
    UBRR1L = (unsigned char) ubrr;
    UCSR1A = 0x00;
    UCSR1B = (1<<RXEN)|(1<<TXEN)|(1<<RXCIE); // Enable TX and RX and recieve interrupt
    UCSR1C = (1<<UCPOL)|(1<<UCSZ0)|(1<<UCSZ1); // 8 data and 1 stop
	sei();

	unsigned char data[] = "Hello from ATmega";
	int i = 0;

	while(1) /* Loop the messsage continously */
	{
		i = 0;
		while(data[i] != 0) /* print the String  "Hello from ATmega" */
		{
			while (!( UCSR1A & (1<<UDRE)));
				UDR1 = data[i];
				i++;
		}
		
		
		/* Sending '\n'  '\r' Character pair helps to format the output properly on console putty Screen */
		/*************************************************************************************************/
		/* Send "\n" Character */
		 while (!( UCSR1A & (1<<UDRE)));
			 UDR1 = '\n';
		
		/* Send "\r" Character */
		 while (!( UCSR1A & (1<<UDRE)));
			 UDR1 = '\r';
		/*------------------------------------------------------------------------------------------------*/
		// while (!(UCSR0A & (1<<RXC)));

		_delay_ms(100);
		
		
	}

}