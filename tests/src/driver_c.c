#include "connection.h"
#include "engine.h"

#include "CppUTest/TestHarness_c.h"


static void connection_battery_test(const char* uri) {
	struct connection_state state = INIT_CONNECTION_STATE;

	Engine* engine = create_engine(uri);
	Connection* conn = engine_connect(engine);
	// If we arrived here no exception launched
	if(state.error) {
		FAIL_C();
	}
	free_engine(engine);
	free_connection(conn);
}

TEST_C(driver_c, connection)
{
	// TODO move this to environment variables
	const char* uri[] = {
#ifdef ORACLE
		"oracle+oracle://BSM_DBA:BSM_DBA_MICH@QBSMOLS2.world/BSM_DBA",
#endif
#ifdef POSTGRES
		"postgres+postgres://localhost/postgres",
#endif
		NULL
	};

	for(unsigned i = 0; uri[i] != NULL; i++) {
		connection_battery_test(uri[i]);
	}
}

