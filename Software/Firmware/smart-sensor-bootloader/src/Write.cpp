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

#define PAGE_SIZE_BYTES 128

uint16_t wordpos = 0;
// uint16_t writeAddress = 0x0000;
uint8_t prog[SPM_PAGESIZE];
uint32_t progAddress = 0;

char *bootReadBuffer()
{
    char temp[] = "NO";
    return temp;
}

// code to reset the prog, this is to make sure there is always some data at every point
void resetProg()
{
    for (int i = 0; i < SPM_PAGESIZE; i++)
    {
        prog[i] = 0xFF;
    }
}

bool writeToBuffer(uint16_t pageAddress, uint8_t *buf, uint8_t byteAmount)
{
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

    for (uint8_t i = 0; i < byteAmount; i += 2)
    {
        // uint16_t w = (uint8_t)buf[i];
        // w += uint8_t((buf[i+1]) << 8);
        prog[wordpos] = buf[i];
        prog[wordpos + 1] = buf[i + 1];

        // //debug print
        // sendString("Word:");
        // char dataArr[2];
        // dataArr[0] = w >> 8;
        // dataArr[1] = w & 0xFF;
        // for (int i = 0; i < 2; i++)
        // {
        //     sendChar(dataArr[i]);
        // }

        // boot_page_fill_safe(pageAddress + i, w);
        // wordpos increase by 2 each time, when it hits page size flash
        wordpos += 2;
        if (wordpos >= SPM_PAGESIZE)
        {
            flashBufferToPage();
            // writeAddress = pageAddress;
            wordpos = 0;
        }
    }
    boot_rww_enable();
    SREG = sreg;

    return true;
}

bool flashBufferToPage()
{
    // boot_page_erase(pageAddress);
    // boot_spm_busy_wait();
    // boot_page_write(pageAddress);
    // boot_spm_busy_wait();
    // take the upper bit which should represent the page
    // uint8_t addressed = (uint8_t)(writeAddress >> 7);

    // uint16_t addressed = writeAddress;
    // sendString("Addressed: ");
    // sendChar(addressed);
    // sendString("AddressRaw:");
    // char addrArr[2];
    // addrArr[0] = writeAddress >> 8;
    // addrArr[1] = writeAddress & 0xFF;
    // for (int i = 0; i < 2; i++)
    // {
    //     sendChar(addrArr[i]);
    // }

    uint16_t i;
    uint8_t sreg;

    // Disable interrupts.
    sreg = SREG;
    cli();

    eeprom_busy_wait();
    boot_page_erase_safe(progAddress);
    boot_spm_busy_wait(); // Wait until the memory is erased.

    sendString("DATA:");
    for (i = 0; i < SPM_PAGESIZE; i += 2)
    {
        // Set up little-endian word.
        uint16_t w = prog[i];
        w += prog[i + 1] << 8;
        char dataArr[2];
        dataArr[0] = w >> 8;
        dataArr[1] = w & 0xFF;
        for (int i = 0; i < 2; i++)
        {
            sendChar(dataArr[i]);
        }
        boot_page_fill_safe(progAddress + i, w);
    }

    boot_page_write_safe(progAddress); // Store buffer in flash page.
    boot_spm_busy_wait();         // Wait until the memory is written.

    // Reenable RWW-section again. We need this if we want to jump back
    // to the application after bootloading.
    boot_rww_enable();

    // Re-enable interrupts (if they were ever enabled).
    SREG = sreg;

    // boot_page_erase_safe(addressed);
    // boot_page_write_safe(addressed);
    resetProg();
    progAddress += PAGE_SIZE_BYTES;
    return true;
}