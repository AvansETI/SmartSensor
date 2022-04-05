/**
 * Seperate class for page interaction
 * @date   : 23 December 2021
 * @author : Tom Kaasenbrood
 * @version: 0.1 development version
 * #todo   : Implement pages
 * @updates
 */


#include <Write.h>
#include <stdint.h>
#include <avr/pgmspace.h>
#include <avr/boot.h>
#include <avr/interrupt.h>
#include <Communication.h>

uint16_t wordpos = 0;
uint16_t writeAddress = 0x0000;

char* bootReadBuffer() {
    char temp[] = "NO";
    return temp;
}

bool writeToBuffer(uint16_t pageAddress, uint8_t *buf, uint8_t byteAmount) {
    // //debug print
    // sendString("Address:");
    // char addrArr[2];
    // addrArr[0] = pageAddress >> 8;
	// addrArr[1] = pageAddress & 0xFF;
    // for (int i = 0; i < 2; i++)
    // {
    //     sendChar(addrArr[i]);
    // }
    
    
    uint8_t sreg;
    sreg = SREG;
    cli();
    eeprom_busy_wait();

    // // debug print
    // sendString("Data:");

    for (uint8_t i = 0; i < byteAmount; i+=2)
    {
        uint16_t w = buf[i];
        w += (buf[i+1]) << 8;

        // //debug print
        // sendString("Word:");
        // char dataArr[2];
        // dataArr[0] = w >> 8;
        // dataArr[1] = w & 0xFF;
        // for (int i = 0; i < 2; i++)
        // {
        //     sendChar(dataArr[i]);
        // }
        
        boot_page_fill_safe(pageAddress + i, w);
        //wordpos increase by 2 each time, when it hits page size flash
        wordpos+=2;
        if (wordpos >= SPM_PAGESIZE)
        {
            flashBufferToPage();
            writeAddress = pageAddress;
            wordpos = 0;
        }
    }
    boot_rww_enable();
    SREG = sreg;
    
    return true;
}

bool flashBufferToPage() {
    // boot_page_erase(pageAddress);
    // boot_spm_busy_wait();
    // boot_page_write(pageAddress);
    // boot_spm_busy_wait();
    //take the upper bit which should represent the page
    // uint8_t addressed = (uint8_t)(writeAddress >> 7);
    uint8_t addressed = (uint8_t)(writeAddress & 0xFE);
    sendString("Addressed: ");
    sendChar(addressed);
    sendString("AddressRaw:");
    char addrArr[2];
    addrArr[0] = writeAddress >> 8;
	addrArr[1] = writeAddress & 0xFF;
    for (int i = 0; i < 2; i++)
    {
        sendChar(addrArr[i]);
    }
    boot_page_erase_safe(addressed);
    boot_page_write_safe(addressed);
    return true;
}