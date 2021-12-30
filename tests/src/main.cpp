#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestHarness_c.h"

TEST_GROUP_C_WRAPPER(driver_c) {};
TEST_C_WRAPPER(driver_c, connection);

TEST_GROUP_C_WRAPPER(driver_oracle_c) {};
TEST_C_WRAPPER(driver_oracle_c, select_number_16_c);

int main(int ac, char** av)
{
	  return RUN_ALL_TESTS(ac, av);
}
