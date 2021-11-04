#include <stdio.h>

#include "CppUTest/TestHarness_c.h"

#include "common.h"
#include "driver.h"

#if TEST_DRIVER == sqlite
#include "sqlite3.h"
#include "sqlite.h"

static struct database_params define_connection() {
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


TEST_C(driver, execute_many)
{
	struct driver driver = INIT_DRIVER(TEST_DRIVER);
	struct database_params db_params = define_connection();

	struct orm_status status = driver.open(&db_params);
	if(status.error) {
		printf(driver.error_message(status.connection));
	}
	CHECK_C(!status.error);
	void *connection = status.connection;

	status = driver.execute_many(connection, "CREATE TABLE t(x INTEGER)", NULL);
	if(status.error) {
		printf(driver.error_message(status.connection));
	}
	CHECK_C(!status.error);

	status = driver.close(connection);
	if(status.error) {
		printf(driver.error_message(status.connection));
	}
	CHECK_C(!status.error);
}

