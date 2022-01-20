#include <string>
#include <memory>
#include <initializer_list>

#include "connection/connection.h"
#include "engine/engine.h"
#include "liborm/type/types.hpp"

#include "CppUTest/TestHarness.h"

TEST_GROUP(driver_oracle){};

static Connection* _test_gconn = NULL;

TEST(driver_oracle, test_global)
{
    if(_test_gconn == NULL) {
        Engine* engine = create_engine_p("oracle+oracle://BSM_DBA:BSM_DBA_MICH@QBSMOLS2.world/BSM_DBA");
        _test_gconn = engine_connect(engine);
        free_engine(engine);
    }

	free_connection(_test_gconn);
	_test_gconn = NULL;
}

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
	#ifdef NDEBUG
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

	/*auto [cursor, err] = conn->execute("select SYSDATE from dual");
	if(err != SQL_ROWS || conn->changes() != 0 || cursor == nullptr) {
		FAIL(conn->error_message());
	}*/

	/* \todo err = cursor->fetch();
	CHECK_TEXT(!err and cursor->changes() > 0 and cursor->nrows() > 0, conn->error_message()); */
}

TEST(driver_oracle, insert_bind_update_select_delete) {
	std::string uri ="oracle+oracle://BSM_DBA:BSM_DBA_MICH@CBSMOLS1.world/BSM_DBA";

	std::unique_ptr<Engine> engine = create_engine(uri);
	std::unique_ptr<Connection> conn = engine->connect();

	std::shared_ptr<TypeEngine const> codpar = orm::String("HI!");
	std::shared_ptr<TypeEngine const> valpar = orm::String("WORLD!");
	std::shared_ptr<TypeEngine const> sitact = orm::String(":)");

	// simply check the syntax work
	auto [cursor, err] = conn->execute("INSERT INTO PARAMETROS(CODPAR, VALPAR, SITACT) VALUES(:codpar, :valpar, :sitact)",
		{{codpar, valpar, sitact}, {orm::String("H2!"), orm::String("H3!"), orm::String("H4!")}});
	if(err != SQL_DONE) {
		FAIL(conn->error_message());
	}

	err = conn->rollback();
	if(err != SQL_DONE) {
		FAIL(conn->error_message());
	}

	auto [cursor2, err2] = conn->execute(
		"INSERT INTO PARAMETROS(CODPAR, VALPAR, SITACT) VALUES(:codpar, :valpar, :sitact)",
		{ codpar, valpar, sitact });
	if(err2 != SQL_DONE || conn->changes() != 1 || cursor2 != nullptr) {
		FAIL(conn->error_message());
	}

	std::tie(cursor, err) = conn->execute("SELECT CODPAR, VALPAR, SITACT FROM PARAMETROS WHERE CODPAR = :codpar AND VALPAR = :valpar AND SITACT = :sitact",
		{codpar, valpar, sitact});
	if(err != SQL_ROWS || conn->changes() != 0 || cursor == nullptr) {
		FAIL(conn->error_message());
	}

	conn_state error = cursor->fetch();
	CHECK_TEXT(!error and cursor->changes() > 0 and cursor->nrows() > 0, conn->error_message());

	TypeEngine* get_sitact = cursor->getValue(0,2);
	TypeEngine* get_codpar = cursor->getValue(0,0);
	TypeEngine* get_valpar = cursor->getValue(0,1);
	CHECK(*get_sitact == *sitact.get());
	CHECK(*get_codpar == *codpar.get());
	CHECK(*get_valpar == *valpar.get());

	err = conn->rollback();
	if(err != SQL_DONE) {
		FAIL(conn->error_message());
	}
}