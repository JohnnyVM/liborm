#include <string>
#include <memory>

#include "CppUTest/TestHarness.h"
#include "connection/connection.h"
#include "engine/engine.h"


TEST_GROUP(driver_oracle){};

TEST(driver_oracle, select_number_16)
{
	conn_state error;
	std::string uri ="oracle+oracle://BSM_DBA:BSM_DBA_MICH@QBSMOLS2.world/BSM_DBA";

	std::shared_ptr<Engine> engine = create_engine(uri);
	std::shared_ptr<Connection> conn = engine->connect();

	auto [cursor, err] = conn->execute("select 16 from dual");
	if(err != SQL_ROWS || conn->changes() != 0 || cursor == nullptr) {
		FAIL(conn->error_message());
	}

	error = cursor->fetch();
	CHECK_TEXT(!error && cursor->changes() > 0, conn->error_message());
}

