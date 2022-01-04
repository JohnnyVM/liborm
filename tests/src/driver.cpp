#include <memory>

#include "engine/engine.h"
#include "connection/connection.h"
#include "connection/state.h"

#include "CppUTest/TestHarness.h"

TEST_GROUP(driver){};

/*static void connection_battery_test(const char* uri) {
	//struct connection_result state = INIT_CONNECTION_RESULT;

	std::shared_ptr<Engine>engine = create_engine(uri);
	std::shared_ptr<Connection>conn = engine->connect();
	// If we arrived here no exception launched
	if(state.state) {
		FAIL("Connection error");
	}
}*/

TEST(driver, connection)
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
		//connection_battery_test(uri[i]);
	}
}

