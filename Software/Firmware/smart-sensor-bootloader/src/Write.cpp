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

char* bootReadBuffer() {
    char temp[] = "NO";
    return temp;
}

bool writeToBuffer(uint16_t pageAddress, uint8_t *buf, uint8_t byteAmount) {
    uint16_t i;
    uint8_t sreg;
    // Disable interrupts.
    sreg = SREG;
    cli();
    eeprom_busy_wait ();
    boot_page_erase (pageAddress);
    boot_spm_busy_wait ();      // Wait until the memory is erased.
    for (i=0; i<SPM_PAGESIZE; i+=2)
    {
        // Set up little-endian word.
        uint16_t w = *buf++;
        w += (*buf++) << 8;
    
        boot_page_fill (pageAddress + i, w);
    }
    boot_page_write (pageAddress);     // Store buffer in flash page.
    boot_spm_busy_wait();       // Wait until the memory is writtesn.
    // Reenable RWW-section again. We need this if we want to jump back
    // to the application after bootloading.
    boot_rww_enable ();
    // Re-enable interrupts (if they were ever enabled).
    SREG = sreg;
    // uint8_t sreg;
    // sreg = SREG;
    // cli();
    // eeprom_busy_wait();
    // for (uint8_t i = 0; i < byteAmount; i+=2)
    // {
    //     uint16_t w = buf[i];
    //     w += (buf[i+1]) << 8;
    //     boot_page_fill(pageAddress + i, w);
    //     //wordpos increase by 2 each time, when it hits page size flash
    //     wordpos+=2;
    //     if (wordpos >= SPM_PAGESIZE)
    //     {
    //         flashBufferToPage(pageAddress);
    //         wordpos = 0;
    //     }
    // }
    // boot_rww_enable();
    SREG = sreg;
    
    return true;
}

bool flashBufferToPage(uint16_t pageAddress) {
    boot_page_erase(pageAddress);
    boot_spm_busy_wait();
    boot_page_write(pageAddress);
    boot_spm_busy_wait();
    return true;
}