#include <string>

#include "CppUTest/TestHarness.h"
#include "connection.h"
#include "engine.h"


TEST_GROUP(driver_oracle){};

TEST(driver_oracle, dual)
{
	conn_error error;
	char uri[] ="oracle+oracle://BSM_DBA:BSM_DBA_MICH@QBSMOLS2.world/BSM_DBA";

	Engine* engine = create_engine(uri);
	Connection* conn = engine->connect();

	auto [cursor, err] = conn->execute("select 1 from dual");
	if(err || conn->changes() != 0 || cursor == nullptr) {
		FAIL("simple select failed");
	}

	error = cursor->fetch();
	CHECK(!error);

	delete cursor;
	delete engine;
	delete conn;
}

