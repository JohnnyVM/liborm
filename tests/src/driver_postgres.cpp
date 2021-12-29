#include <string>

#include "engine/engine.h"
#include "connection/connection.h"

#include "CppUTest/TestHarness.h"

TEST_GROUP(driver_postgres){};

TEST(driver_postgres, dual)
{
	struct connection_result state = INIT_CONNECTION_RESULT;
	char uri[] ="postgres+postgres://localhost/postgres";

	Engine* engine = create_engine(uri);
	Connection* conn = engine_connect(engine);

	state = conn->execute("select 1");
	if(state.state) {
		FAIL("simple select failed");
	}

	delete engine;
	delete conn;
}

