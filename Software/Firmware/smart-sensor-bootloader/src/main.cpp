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

char offbuffer[2];
char hexbuffer[2];
bool jumpcommand = false;

/* When a character is received on the serial bus, this interrupt is called. */
ISR(USART0_RX_vect) {
    char c = UDR0;
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
					while (!(UCSR0A & (1<<UDRE)));
					{
						UDR0 = shutdown[i];
						i++;
					}
					
				}
				
				offbuffer[0] = 'P';
				offbuffer[1] = 'W';

                jumpcommand = true;
			} else {
				offbuffer[1] = c;
			}
			
		}
		
	} else if (c == 'O')
	{
		offbuffer[0] = c;
	}

	if (hexbuffer[0] == 'H')
	{
		if (hexbuffer[1] == 'E')
		{
			if (c == 'X')
			{
				int i = 0;
				unsigned char hextest[] = "Pretend this is a file. \n";
				while (hextest[i] != 0)
				{
					while (!(UCSR0A & (1<<UDRE)));
					{
						UDR0 = hextest[i];
						i++;
					}
					
				}
				
				hexbuffer[0] = 'N';
				hexbuffer[1] = 'O';
			}
			
		} else if (c == 'E')
		{
			hexbuffer[1] = c;
		}
		
		
	} else if (c == 'H')
	{
		hexbuffer[0] = c;
	}
	
	
	
	
	
	unsigned char message[] = "Character recieved: ";
	int i = 0;
		while(message[i] != 0) /* print the String  "Character recieved: + The character" */
		{
			while (!( UCSR0A & (1<<UDRE)));
				UDR0 = message[i];
				i++;
		}
		while (!( UCSR0A & (1<<UDRE)));
				UDR0 = c;
		while (!( UCSR0A & (1<<UDRE)));
				UDR0 = '\n\r';
}

void boot_program_page (uint32_t page, uint8_t *buf)
{
	uint16_t i;
	uint8_t sreg;

	// Disable interrupts.

	sreg = SREG;
	cli();

	eeprom_busy_wait ();

	boot_page_erase (page);
	boot_spm_busy_wait ();      // Wait until the memory is erased.

	for (i=0; i<SPM_PAGESIZE; i+=2)
	{
		// Set up little-endian word.

		uint16_t w = *buf++;
		w += (*buf++) << 8;

		boot_page_fill (page + i, w);
	}

	boot_page_write (page);     // Store buffer in flash page.
	boot_spm_busy_wait();       // Wait until the memory is written.

	// Reenable RWW-section again. We need this if we want to jump back
	// to the application after bootloading.

	boot_rww_enable ();

	// Re-enable interrupts (if they were ever enabled).

	SREG = sreg;
}

int main(void) {
	offbuffer[0] = 'P';
	offbuffer[1] = 'W';
	hexbuffer[0] = 'N';
	hexbuffer[1] = 'O';
	uint32_t baudrate = 9600;
    uint32_t ubrr = 20000000 / 16 / 9600-1;//((20000000 -((baudrate) * 8L)) / ((baudrate) * 16UL));

    UBRR0H = (unsigned char) (ubrr >> 8); // Configuration of the baudrate
    UBRR0L = (unsigned char) ubrr;
    UCSR0A = 0x00;
    UCSR0B = (1<<RXEN)|(1<<TXEN)|(1<<RXCIE); // Enable TX and RX and recieve interrupt
    UCSR0C = (1<<UCPOL)|(1<<UCSZ0)|(1<<UCSZ1); // 8 data and 1 stop
	sei();

	unsigned char mes[] = "Loop reached";
	int b = 0;
	while(mes[b] != 0) /* print the String  "Hello from ATmega" */
		{
			while (!( UCSR0A & (1<<UDRE)));
				UDR0 = mes[b];
				b++;
		}

	unsigned char data[] = "Hello from ATmega";
	int i = 0;

	while(1) /* Loop the messsage continously */
	{
		i = 0;
		while(data[i] != 0) /* print the String  "Hello from ATmega" */
		{
			while (!( UCSR0A & (1<<UDRE)));
				UDR0 = data[i];
				i++;
		}
		
		/* Send "\n" Character */
		 while (!( UCSR0A & (1<<UDRE)));
			UDR0 = '\n';
		
		/* Send "\r" Character */
		 while (!( UCSR0A & (1<<UDRE)));
			UDR0 = '\r';

		_delay_ms(100);

        if (jumpcommand)
        {
            int i = 0;
				unsigned char shutdown[] = "Jumping to other program. \n";
				while (shutdown[i] != 0)
				{
					while (!(UCSR0A & (1<<UDRE)));
					{
						UDR0 = shutdown[i];
						i++;
					}
					
				}
            asm("JMP 0x0000");
        }
        
		
		
	}

}