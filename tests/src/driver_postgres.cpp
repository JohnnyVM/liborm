#include <string>

#include "engine.h"
#include "connection.h"

#include "CppUTest/TestHarness.h"

TEST_GROUP(driver_postgres){};

TEST(driver_postgres, dual)
{
	struct connection_state state = INIT_CONNECTION_STATE;
	char uri[] ="postgres+postgres://localhost/postgres";

	Engine* engine = create_engine(uri);
	Connection* conn = engine_connect(engine);

	state = conn->execute("select 1");
	if(state.error) {
		FAIL("simple select failed");
	}

	delete engine;
	delete conn;
}

