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
	CHECK_TEXT(!error and cursor->changes() > 0 and cursor->nrows() > 0, conn->error_message());

	orm::TypeEngine* val = cursor->getValue(0,0);
	CHECK_TEXT(dynamic_cast<orm::type::Numeric*>(val), "invalid returned type");
	const orm::type::Numeric& num = *cursor->getValue(0,0);
	CHECK(num == 16);
}

TEST(driver_oracle, select_char_16)
{
	conn_state error;
	std::string uri ="oracle+oracle://BSM_DBA:BSM_DBA_MICH@QBSMOLS2.world/BSM_DBA";

	std::shared_ptr<Engine> engine = create_engine(uri);
	std::shared_ptr<Connection> conn = engine->connect();

	auto [cursor, err] = conn->execute("select '16' from dual");
	if(err != SQL_ROWS || conn->changes() != 0 || cursor == nullptr) {
		FAIL(conn->error_message());
	}

	error = cursor->fetch();
	CHECK_TEXT(!error and cursor->changes() > 0 and cursor->nrows() > 0, conn->error_message());

	orm::TypeEngine* val = cursor->getValue(0,0);
	CHECK_TEXT(dynamic_cast<orm::type::String*>(val), "invalid returned type");
	const orm::type::String& num = *cursor->getValue(0,0);
	CHECK(num == "16");
}
