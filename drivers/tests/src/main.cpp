#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestHarness_c.h"

/** For each C test group */
TEST_GROUP_C_WRAPPER(driver)
{
    TEST_GROUP_C_SETUP_WRAPPER(driver); /** optional */
    TEST_GROUP_C_TEARDOWN_WRAPPER(driver); /** optional */
};

TEST_C_WRAPPER(driver, open);
TEST_C_WRAPPER(driver, execute_many);

int main(int ac, char** av)
{
    return CommandLineTestRunner::RunAllTests(ac, av);
}
