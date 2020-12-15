/**
 * Entry point of the application
 * @date 12 May 2020
 * @author Patrick de Jong, Paul Hobbel, Sergen Peker, Carlos Cadel
 */
#ifndef UNIT_TEST
#include <boardsupport.h>
#include <board-support/drivers/TWIDriver.h>
#include <util/Composer.h>
#include <board-support/util/PinManager.h>

int main() {
    Composer composer;
	//SerialLogger::print("===========================================\n\nStarting Smart Sensor\n\n===========================================\n");

	//SerialLogger::info("Initializing...");
	
    TWIDriver::init();
    composer.init();

    PinManager::set_mode(STATUS_LED_1_PIN, OUTPUT);
    PinManager::set_mode(STATUS_LED_2_PIN, OUTPUT);

    _delay_ms(1000);

	//SerialLogger::info("Starting update loop");

    for (;;) {
        composer.update();
        _delay_ms(500);
    }
    return 0;
}


#endif