#include <string>
#include <memory>

#include "connection/connection.h"
#include "engine/engine.h"
#include "type/types.hpp"

#include "CppUTest/TestHarness.h"

TEST_GROUP(driver_oracle){};

TEST(driver_oracle, select_char_16)
{
	conn_state error;
	std::string uri ="oracle+oracle://BSM_DBA:BSM_DBA_MICH@QBSMOLS2.world/BSM_DBA";

	std::shared_ptr<Engine> engine = create_engine(uri);
	std::unique_ptr<Connection> conn = engine->connect();

	auto [cursor, err] = conn->execute("select '16' AS STRING from dual");
	if(err != SQL_ROWS || conn->changes() != 0 || cursor == nullptr || cursor->changes() != 0 || cursor->nrows() != 0) {
		FAIL(conn->error_message());
	}

	error = cursor->fetch();
	CHECK_TEXT(!error and cursor->changes() > 0 and cursor->nrows() > 0, conn->error_message());

	TypeEngine* val = cursor->getValue(0,0);
	CHECK_TEXT(dynamic_cast<orm::type::String*>(val), "invalid returned type");
	const orm::type::String& num = dynamic_cast<orm::type::String&>(*cursor->getValue(0,0));
	CHECK(num == "16");
	CHECK_EQUAL(cursor->size("STRING"),3);
	CHECK_EQUAL(cursor->size(0U),3);
}

TEST(driver_oracle, select_number_16)
{
	std::string uri ="oracle+oracle://BSM_DBA:BSM_DBA_MICH@QBSMOLS2.world/BSM_DBA";

	std::shared_ptr<Engine> engine = create_engine(uri);
	std::unique_ptr<Connection> conn = engine->connect();

	auto [cursor, err] = conn->execute("select 16 from dual");
	if(err != SQL_ROWS || conn->changes() != 0 || cursor == nullptr) {
		FAIL(conn->error_message());
	}

	conn_state error = cursor->fetch();
	CHECK_TEXT(!error and cursor->changes() > 0 and cursor->nrows() > 0, conn->error_message());

	TypeEngine* val = cursor->getValue(0,0);
	CHECK_TEXT(dynamic_cast<orm::type::Numeric*>(val), "invalid returned type");
	const orm::type::Numeric& num = dynamic_cast<orm::type::Numeric&>(*cursor->getValue(0,0));
	CHECK(num == 16);

	std::tie(cursor, err) = conn->execute("SELECT CAST(-1 AS NUMBER(19,9)) AS LONG_DOUBLE FROM DUAL");
	if(err != SQL_ROWS || conn->changes() != 0 || cursor == nullptr) {
		FAIL(conn->error_message());
	}

	CHECK_EQUAL(std::string("LONG_DOUBLE"), cursor->name(0));

	error = cursor->fetch();
	CHECK_TEXT(!error and cursor->changes() > 0 and cursor->nrows() > 0, conn->error_message());
	const orm::type::Numeric& minus = dynamic_cast<orm::type::Numeric&>(*cursor->getValue(0,0));
	CHECK(minus == -1);

	TypeEngine* nval = cursor->getValue(0, 0);
	TypeEngine* cval = cursor->getValue(0, cursor->number("LONG_DOUBLE"));
	TypeEngine* dval = cursor->getValue(0, "LONG_DOUBLE");
	CHECK_EQUAL(nval, cval);
	CHECK_EQUAL(dval, cval);

	std::tie(cursor, err) = conn->execute("SELECT CAST(9999999999.999999989 AS NUMBER(19,9)) AS LONG_DOUBLE FROM DUAL");
	if(err != SQL_ROWS || conn->changes() != 0 || cursor == nullptr) {
		FAIL(conn->error_message());
	}

	error = cursor->fetch();
	CHECK_TEXT(!error and cursor->changes() > 0 and cursor->nrows() > 0, conn->error_message());
	const orm::type::Numeric& canido = dynamic_cast<orm::type::Numeric&>(*cursor->getValue(0,0));
	CHECK(canido == std::decimal::decimal128(9999999999.999999989DL));
}

TEST(driver_oracle, acbuffer)
{
	std::string uri ="oracle+oracle://BSM_DBA:BSM_DBA_MICH@QBSMOLS2.world/BSM_DBA";

	std::unique_ptr<Engine> engine = create_engine(uri);
	std::unique_ptr<Connection> conn = engine->connect();

	auto [cursor1, err1] = conn->execute("select 16 from dual");
	if(err1 != SQL_ROWS || conn->changes() != 0 || cursor1 == nullptr) {
		FAIL(conn->error_message());
	}

	auto [cursor0, err0] = conn->execute("SELECT CAST(-1 AS NUMBER(19,9)) AS LONG_DOUBLE FROM DUAL");
	if(err0 != SQL_ROWS || conn->changes() != 0 || cursor0 == nullptr) {
		FAIL(conn->error_message());
	}

	CHECK_EQUAL(std::string("LONG_DOUBLE"), cursor0->name(0));

	// this test fail in debug mode becouse assert
	#ifndef NDEBUG
	auto [cursor2, err2] = conn->execute("SELECT CAST(9999999999.999999999 AS NUMBER(19,9)) AS LONG_DOUBLE FROM DUAL");
	CHECK_TEXT(err2 == SQL_MAXOPENCURSORS, "Not returned SQL_MAXOPENCURSORS");
	#endif
}

TEST(driver_oracle, select_false) {
	conn_state error;
	std::string uri ="oracle+oracle://BSM_DBA:BSM_DBA_MICH@QBSMOLS2.world/BSM_DBA";

	std::unique_ptr<Engine> engine = create_engine(uri);
	std::unique_ptr<Connection> conn = engine->connect();

	auto [cursor, err] = conn->execute("select '16' from dual  WHERE 1 = 0");
	if(err != SQL_ROWS || conn->changes() != 0 || cursor == nullptr || cursor->changes() != 0 || cursor->nrows() != 0) {
		FAIL(conn->error_message());
	}

	error = cursor->fetch();
	CHECK_TEXT(!error and cursor->changes() == 0 and cursor->nrows() == 0, conn->error_message());
}

TEST(driver_oracle, select_date) {
	std::string uri ="oracle+oracle://BSM_DBA:BSM_DBA_MICH@QBSMOLS2.world/BSM_DBA";

	std::unique_ptr<Engine> engine = create_engine(uri);
	std::unique_ptr<Connection> conn = engine->connect();

	auto [cursor, err] = conn->execute("select SYSDATE from dual");
	if(err != SQL_ROWS || conn->changes() != 0 || cursor == nullptr) {
		FAIL(conn->error_message());
	}

	/* \todo err = cursor->fetch();
	CHECK_TEXT(!err and cursor->changes() > 0 and cursor->nrows() > 0, conn->error_message()); */
}

TEST(driver_oracle, insert_bind_update_select_delete) {
	std::string uri ="oracle+oracle://BSM_DBA:BSM_DBA_MICH@CBSMOLS1.world/BSM_DBA";

	std::unique_ptr<Engine> engine = create_engine(uri);
	std::unique_ptr<Connection> conn = engine->connect();

	orm::type::String codpar(3, "HI!");
	orm::type::String valpar(8, "WORLD!");
	orm::type::String sitact(3, ":)");

	/*auto [cursor, err] = conn->execute("INSERT INTO PARAMETROS(CODPAR, VALPAR, SITACT) VALUES(:codpar, :valpar, :sitact)");
	if(err != SQL_DONE) {
		FAIL(conn->error_message());
	}

	conn->rollback();
	if(err != SQL_DONE) {
		FAIL(conn->error_message());
	}*/
}