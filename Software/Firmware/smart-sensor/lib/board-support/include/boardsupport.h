/**
 * Base BoardSupport configuration
 * NOTE: Do not change any values in here
 *       make changes in the board definitions
 */

#ifndef BOARD_SUPPORT_BOARDSUPPORT_H
#define BOARD_SUPPORT_BOARDSUPPORT_H

#include <avr/io.h>
#include <math.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdutils.h>
#include <util/twi.h>
#include <util/delay.h>

/*********************************************
 * USART 0
 *********************************************/

/**
 * Whether USART0 should be enabled
 */
#define USART0_ENABLED          1

/**
 * Baud rate for USART0
 */
#define USART0_BAUD_RATE        9600

/**
 * 0: Both Receive and Transmit over USART0
 * 1: Only Receive
 * 2: Only Transmit
 */
#define USART0_TX_RX            0


/*********************************************
 * USART 1
 *********************************************/

/**
 * Whether USART1 should be enabled
 */
#define USART1_ENABLED          1

/**
 * Baud rate for USART1
 */
#define USART1_BAUD_RATE        9600

/**
 * 0: Both Receive and Transmit over USART1
 * 1: Only Receive
 * 2: Only Transmit
 */
#define USART1_TX_RX            0


/*********************************************
 * USART 2
 *********************************************/

/**
 * Whether USART2 should be enabled
 */
#define USART2_ENABLED          1

/**
 * Baud rate for USART2
 */
#define USART2_BAUD_RATE        9600

/**
 * 0: Both Receive and Transmit over USART1
 * 1: Only Receive
 * 2: Only Transmit
 */
#define USART2_TX_RX            0


/**
 * TWI DRIVER
 */

#define TWI0_ENABLED            1

/**
 * TWI0 SCL Clock in Hz
 */
#define TWI0_SCL_CLOCK          100'000UL

#define TWI1_ENABLED            1

/**
 * TWI1 SCL Clock in Hz
 */
#define TWI1_SCL_CLOCK          10'000UL

/**
 * Digital Driver
 */

/**
 * PWM Driver
 */
#define PWM_MAX_DUTY_CYCLE  100


/**
 * StateMachine
 */

#define MAX_NUM_STATES      4

#if defined(BOARD_REVISION_03)
    #include "boards/board-r03.h"
#elif defined(BOARD_REVISION_10)
    #include "boards/board-r10.h"
#elif defined(BOARD_REVISION_11)
    #include "boards/board-r11.h"
#else
    #error "No supported board revision was defined!"
#endif


#endif //BOARD_SUPPORT_BOARDSUPPORT_H
