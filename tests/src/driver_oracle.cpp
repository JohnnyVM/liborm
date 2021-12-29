#include <string>

#include "CppUTest/TestHarness.h"
#include "connection.h"
#include "engine.h"


TEST_GROUP(driver_oracle){};

TEST(driver_oracle, dual)
{
	conn_state error;
	char uri[] ="oracle+oracle://BSM_DBA:BSM_DBA_MICH@QBSMOLS2.world/BSM_DBA";

	Engine* engine = create_engine(uri);
	Connection* conn = engine->connect();

	auto [cursor, err] = conn->execute("select 1 from dual");
	if(err != SQL_ROWS || conn->changes() != 0 || cursor == nullptr) {
		FAIL(conn->error_message());
	}

	error = cursor->fetch();
	CHECK_TEXT(!error && cursor->changes() > 0, conn->error_message());

	delete cursor;
	delete engine;
	delete conn;
}

