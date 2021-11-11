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
			while (!( UCSR0A & (1<<UDRE)));
				UDR0 = message[i];
				i++;
		}
		while (!( UCSR0A & (1<<UDRE)));
				UDR0 = c;
		while (!( UCSR0A & (1<<UDRE)));
				UDR0 = '\n\r';
}

int main(void) {
	offbuffer[0] = 'P';
	offbuffer[1] = 'W';
	uint32_t baudrate = 9600;
    uint32_t ubrr = 20000000 / 16 / 9600-1;//((20000000 -((baudrate) * 8L)) / ((baudrate) * 16UL));

    UBRR0H = (unsigned char) (ubrr >> 8); // Configuration of the baudrate
    UBRR0L = (unsigned char) ubrr;
    UCSR0A = 0x00;
    UCSR0B = (1<<RXEN)|(1<<TXEN)|(1<<RXCIE); // Enable TX and RX and recieve interrupt
    UCSR0C = (1<<UCPOL)|(1<<UCSZ0)|(1<<UCSZ1); // 8 data and 1 stop
	sei();

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
		
		
	}

}