#include <unity.h>

#include "state/StateMachineTests.h"
#include "util/PinManagerTests.h"
#include "util/PinUtilTests.h"
#include "drivers/TWIDriverTests.hpp"
#include "drivers/UsuartDriver.hpp"
#include "drivers/PWMDriverTests.hpp"

int main() {
    UNITY_BEGIN();

    test_state_StateMachineTests::run();
    test_util_PinUtil::run();
    test_util_PinManager::run();
    test_drivers_TWIDriverTests::run();
    test_drivers_UsartDriver::run();
    test_drivers_PWMDriversTests::run();

    return UNITY_END();
}
