#include <stdio.h>

#include "CppUTest/TestHarness_c.h"

#include "sqlite3.h"

#include "driver.h"
#include "common.h"
#include "close.h"
#include "open.h"
#include "error_message.h"


TEST_GROUP_C_SETUP(driver)
{
}

TEST_GROUP_C_TEARDOWN(driver)
{
}

#if TEST_DRIVER == sqlite
struct database_params define_connection() {
	struct database_params out =
	{
		. database = ":memory:",
		.flags = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_MEMORY,
	};

	return out;
}
#else
#error "No know driver defined"
#endif


TEST_C(driver, open)
{
	struct driver driver = INIT_DRIVER(TEST_DRIVER);
	struct database_params db_params = define_connection();

	struct orm_status status = driver.open(&db_params);
	if(status.error) {
		printf(driver.error_message(status.connection));
	}
	CHECK_C(!status.error);
	void *connection = status.connection;

	status = driver.close(connection);
	if(status.error) {
		printf(driver.error_message(status.connection));
	}
	CHECK_C(!status.error);

}

