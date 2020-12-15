#ifndef INETWORK_TESTS_H_
#define INETWORK_TESTS_H_

#include <unity.h>
#include <board-support/communication/INetwork.h>

namespace test_communication_INetworkTests {

    // TODO: Code written for INetwork, which has rendered itself moot. Code can be re-used for subclasses implementing INetwork.
    INetwork *network = nullptr;

    void test_INetwork_not_null() {
        TEST_ASSERT_NOT_NULL(network)
    }

    void test_INetwork_read_not_null() {
        TEST_ASSERT_NOT_NULL(network->read())
    }

    void test_INetwork_read_contains_bytes() {
        TEST_ASSERT_GREATER_THAN(0, (sizeof((network->read())) / sizeof((network->read())[0])));
    }

    void test_INetwork_send() {
        TEST_ASSERT_FALSE(network->send(nullptr))
        byte test_data[1] = {0};
        TEST_ASSERT_TRUE(network->send(test_data))
    }

    void run() {
        RUN_TEST(test_INetwork_not_null);
        RUN_TEST(test_INetwork_read_not_null);
        RUN_TEST(test_INetwork_read_contains_bytes);
        RUN_TEST(test_INetwork_send);
    }

}

#endif