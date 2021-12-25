#include "engine.h"
#include "connection.h"

#include "CppUTest/TestHarness.h"

TEST_GROUP(driver){};

static void connection_battery_test(const char* uri) {
	struct connection_state state = INIT_CONNECTION_STATE;

	Engine* engine = create_engine(uri);
	Connection* conn = engine_connect(engine);
	// If we arrived here no exception launched
	if(state.error) {
		FAIL("Connection error");
	}
	delete engine;
	delete conn;
}

TEST(driver, connection)
{
	// TODO move this to environment variables
	const char* uri[] = {
#ifdef DRIVER_ORACLE
		"oracle+oracle://BSM_DBA:BSM_DBA_MICH@QBSMOLS2.world/BSM_DBA",
#endif
#ifdef DRIVER_POSTGRES
		"postgres+postgres://localhost/postgres",
#endif
		NULL
	};

	for(unsigned i = 0; uri[i] != NULL; i++) {
		connection_battery_test(uri[i]);
	}
}

