#include <unity.h>

#include "drivers/THSDriverTests.hpp"
#include "drivers/LightDriverTests.hpp"

int main() {
    UNITY_BEGIN();

    test_drivers_THSDriverTests::run();
    test_drivers_LightDriverTests::run();

    return UNITY_END();
}
