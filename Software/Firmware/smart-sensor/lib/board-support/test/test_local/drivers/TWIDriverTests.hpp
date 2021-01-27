//
// Created by paulh on 5/12/2020.
//

#ifndef BOARD_SUPPORT_TWIDRIVERTESTS_HPP
#define BOARD_SUPPORT_TWIDRIVERTESTS_HPP

#define TWI_USE_INSTANCE 0

#include <board-support/drivers/TWIDriver.h>

namespace test_drivers_TWIDriverTests {
    class TestTWIDriver : TWIDriver {
        public:
            TestTWIDriver() : TWIDriver(TWI0) {}

            void pStart() {
                twi_start();
            }
            void pStop() {
                twi_stop();
            }
            void pSelect() {
                twi_select(0xE0, TWIDriver::Write);
            }
            uint8_t pRead() {
                return twi_read_ack();
            }
            void pWrite() {
                twi_write(0x01);
            }
    };

    void test_TWIDriver_init() {
        TWIDriver::init();

        TEST_ASSERT_EQUAL(0x20, TWBR0);
    }

    void test_TWIDriver_start() {
        TestTWIDriver driver;
        driver.pStart();

        // Assert TWCR0 goes into start phase
        TEST_ASSERT_EQUAL((1 << TWINT) | (1 << TWSTA) | (1 << TWEN), TWCR0);
    }

    void test_TWIDriver_stop() {
        TestTWIDriver driver;
        driver.pStop();

        TEST_ASSERT_EQUAL((1 << TWINT) | (1 << TWEN) | (1 << TWSTO), TWCR0);
    }

    void test_TWIDriver_select() {
        TestTWIDriver driver;
        driver.pSelect();

        TEST_ASSERT_EQUAL(((0xE0 & 0xFE) | TW_WRITE), TWDR0);
    }

    void test_TWIDriver_read() {
        TestTWIDriver driver;

        TWDR0 = 0x20;
        TEST_ASSERT_EQUAL(0x20, driver.pRead());
    }

    void test_TWIDriver_write() {
        TestTWIDriver driver;
        driver.pWrite();

        TEST_ASSERT_EQUAL(TWDR0, 0x01);
    }

    void run() {
        RUN_TEST(test_TWIDriver_init);
        RUN_TEST(test_TWIDriver_start);
        RUN_TEST(test_TWIDriver_stop);
        RUN_TEST(test_TWIDriver_select);
        RUN_TEST(test_TWIDriver_read);
        RUN_TEST(test_TWIDriver_write);
    }
}

#endif //BOARD_SUPPORT_TWIDRIVERTESTS_HPP
