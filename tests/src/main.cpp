#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestHarness_c.h"

TEST_GROUP_C_WRAPPER(driver_c) {};
TEST_C_WRAPPER(driver_c, connection);

#ifdef ORACLE
TEST_GROUP_C_WRAPPER(driver_oracle_c) {};
TEST_C_WRAPPER(driver_oracle_c, select_number_16_c);
#endif

int main(int argc, char** argv)
{
	MemoryLeakWarningPlugin::turnOffNewDeleteOverloads();
	return CommandLineTestRunner::RunAllTests(argc, argv);
}
