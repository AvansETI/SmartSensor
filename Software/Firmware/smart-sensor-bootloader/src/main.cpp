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
#include <Communication.h>
#include <stdio.h>
#include <StateMachine.h>
#include <Write.h>

typedef enum
{
	bootState,
	receiveState,
	writeState,
	executeState,
	totalState
} states;

typedef enum
{
	bootEvent,
	receiveEvent,
	writeEvent,
	flashEvent,
	executeEvent,
	doneEvent,
	timeoutEvent,
	totalEvent
} events;

FiniteStateMachine stateMachine(totalState, totalEvent);
uint8_t dataToWrite[16];
uint16_t addressToWrite;
uint8_t bytesToWrite;
uint8_t updatedelay;

// code to check if there was an update in progress, if there was a command should be sent to the updater about it
// TODO: Actually implement update check
bool checkForUpdateInProgress()
{
	return false;
}

// handlers for various events
// raiseevents in the handlers were there for testing and are currently commented out
// events should be raised by other methods, not these events themselves

// handler for the bootstate, handling initial setup and can go to the recievestate or executestate in case of timeout
void bootHandler()
{
	// char bootmes[] = "Boot\n";
	// sendString(bootmes);
	// stateMachine.raiseEvent(bootEvent);
	if (checkForUpdateInProgress())
	{
		// go to recieve state, that's where progress should be
		stateMachine.raiseEvent(bootEvent);
	}
	else
	{
		// send ID info
		sendString("V0.9");

		// when update char is received go to receivestate
		// TODO: add timeout when ended
		if (isCharReceived())
		{
			if (readChar() == 'U')
			{
				resetProg();
				sendChar('R');
				stateMachine.raiseEvent(bootEvent);
			}
		}
		else
		{
			// if there is no update for some time it should go the main program
			updatedelay++;
			if (updatedelay >= 20)
			{
				sendChar('T');
				stateMachine.raiseEvent(timeoutEvent);
			}
		}
	}
}

// handler for the receive state, handles the receiving of updates and other characters, can go to the write state
void receiveHandler()
{

	// Array for holding the received chars, probably won't exceed 45-ish
	char receivedchars[50];
	// timeout variable, do not put it too low or the code won't work
	uint8_t timeout = 250;
	// length of the array, should always be the same as receivedchars length
	uint8_t length = 50;
	if (readLine(receivedchars, timeout, length))
	{
		// variable to hold the gathered data
		uint8_t data[16];
		for (int i = 0; i < 16; i++)
		{
			data[i] = 0;
		}

		// variable to hold the gotten address
		uint16_t address;
		uint8_t bytesAmount;
		if (isValidLine(receivedchars, data, &address, &bytesAmount))
		{
			// if the line is valid, put the gathered data and address in their variables and go to the write state
			for (int i = 0; i < 16; i++)
			{
				dataToWrite[i] = data[i];
			}
			addressToWrite = address;
			bytesToWrite = bytesAmount;
			stateMachine.raiseEvent(receiveEvent);
		}
		// when done go to the execute state
		else if (isDone())
		{
			flashBufferToPage();
			sendChar('X');
			stateMachine.raiseEvent(doneEvent);
		}
	}
	else
	{
		// error with Processing line
		sendChar('W');
	}
}

// method for handling the writing to the buffer and the flashing of the buffer
void writeHandler()
{
	// char wrimes[] = "Write\n";
	// sendString(wrimes);
	// stateMachine.raiseEvent(writeEvent);

	// address is actually full intelhex address and as such is simply passed along
	writeToBuffer(addressToWrite, dataToWrite, bytesToWrite);

	// DEBUG
	//  //print code for testing
	//  sendString("Address:");
	//  char stringarr[2];
	//  stringarr[0] = addressToWrite >> 8;
	//  stringarr[1] = addressToWrite & 0xFF;
	//  // sendString(stringarr);
	//  for (int i = 0; i < 2; i++)
	//  {
	//  	sendChar(stringarr[i]);
	//  }

	// sendString("Data:");
	// int i = 0;
	// while (i < bytesToWrite)
	// {
	// 	if (dataToWrite[i] != -1)
	// 	{
	// 		sendChar(dataToWrite[i]);
	// 	}
	// 	i++;
	// }

	// when done with a line, send X and go back to receivestate
	sendChar('X');
	stateMachine.raiseEvent(flashEvent);
}
// handler for execution of program, simply jumps to address 0x0000
void executeHandler()
{
	char exemes[] = "Message written\n";
	sendString(exemes);
	// stateMachine.raiseEvent(executeEvent);
	asm("jmp 0");
}

int main(void)
{

	DDRD |= 1 << PD4;
	PORTD |= 1 << PD4;
	_delay_ms(100);
	PORTD &= ~(1 << PD4);
	_delay_ms(1000);
	initSerial();
	updatedelay = 0;
	resetAddress();

	// add necessary data to state machine
	// add states to machine
	stateMachine.addState(bootState, bootHandler);
	stateMachine.addState(receiveState, receiveHandler);
	stateMachine.addState(writeState, writeHandler);
	stateMachine.addState(executeState, executeHandler);

	// add transitions to machine
	stateMachine.addTransition(bootState, bootEvent, receiveState);
	stateMachine.addTransition(receiveState, receiveEvent, writeState);
	stateMachine.addTransition(writeState, writeEvent, executeState);
	stateMachine.addTransition(executeState, executeEvent, bootState);
	stateMachine.addTransition(writeState, flashEvent, receiveState);
	stateMachine.addTransition(receiveState, doneEvent, executeState);
	stateMachine.addTransition(bootState, timeoutEvent, executeState);

	// setup state machine
	stateMachine.setup(bootState);

	while (1)
	{
		stateMachine.loop();
		_delay_ms(1000);
	}
}