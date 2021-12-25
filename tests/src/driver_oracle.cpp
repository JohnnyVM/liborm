#include <string>

#include "CppUTest/TestHarness.h"
#include "connection.h"
#include "engine.h"


TEST_GROUP(driver_oracle){};

TEST(driver_oracle, dual)
{
	struct connection_state state = INIT_CONNECTION_STATE;
	char uri[] ="oracle+oracle://BSM_DBA:BSM_DBA_MICH@QBSMOLS2.world/BSM_DBA";

	Engine* engine = create_engine(uri);
	engine->foo();
	Connection* conn = engine->connect();

	state = conn->execute_many("select 1 from dual", nullptr);
	if(state.error && state.tuples_ok && state.cursor && state.changes == 0) {
		FAIL("simple select failed");
	}

	Cursor* c = state.cursor;
	state = c->open();
	CHECK(!state.error);
	state = c->fetch();
	CHECK(!state.error && state.changes == 1 && c->changes() == 1);

	delete state.cursor;
	delete engine;
	delete conn;
}

