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

char* bootReadBuffer() {
    char temp[] = "NO";
    return temp;
}

bool writeToBuffer(uint32_t pageNo, uint8_t *buf) {
    uint16_t i;
    uint8_t sreg;
    // Disable interrupts.
    sreg = SREG;
    cli();
    eeprom_busy_wait ();
    boot_page_erase (pageNo);
    boot_spm_busy_wait ();      // Wait until the memory is erased.
    for (i=0; i<SPM_PAGESIZE; i+=2)
    {
        // Set up little-endian word.
        uint16_t w = *buf++;
        w += (*buf++) << 8;
    
        boot_page_fill (pageNo + i, w);
    }
    boot_page_write (pageNo);     // Store buffer in flash page.
    boot_spm_busy_wait();       // Wait until the memory is written.
    // Reenable RWW-section again. We need this if we want to jump back
    // to the application after bootloading.
    boot_rww_enable ();
    // Re-enable interrupts (if they were ever enabled).
    SREG = sreg;
    return true;
}

bool flashBufferToPage() {
    return true;
}