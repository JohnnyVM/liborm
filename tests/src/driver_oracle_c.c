#include <string.h>

#include "connection/connection.h"
#include "engine/engine.h"
#include "liborm/type/engine.h"

#include "CppUTest/TestHarness_c.h"

TEST_C(driver_oracle_c, select_char_16_c)
{
	conn_state error;
	char uri[] ="oracle+oracle://BSM_DBA:BSM_DBA_MICH@QBSMOLS2.world/BSM_DBA";

	Engine* engine = create_engine_p(uri);
	Connection* conn = engine_connect(engine);

	struct connection_result res = connection_execute(conn,"select '16' from dual");
	if(res.state != SQL_ROWS || connection_changes(conn) != 0 || res.cursor == NULL) {
		FAIL_TEXT_C("Simple select failed");
	}

	error = cursor_fetch(res.cursor);
	CHECK_C_TEXT(!error && cursor_changes(res.cursor) > 0 && cursor_nrows(res.cursor) > 0, connection_error_message(conn));

	TypeEngine* val = cursor_getValue(res.cursor, 0, 0);
	char test[5];
	int len = column_as_char(val, test, sizeof test);
	CHECK_C(len == 2 && !strncmp(test, "16", sizeof test));

	free_cursor(res.cursor);
	free_engine(engine);
	free_connection(conn);
}

TEST_C(driver_oracle_c, select_number_16_c)
{
	conn_state error;
	char uri[] ="oracle+oracle://BSM_DBA:BSM_DBA_MICH@QBSMOLS2.world/BSM_DBA";

	Engine* engine = create_engine_p(uri);
	Connection* conn = engine_connect(engine);

	struct connection_result res = connection_execute(conn,"select 16 from dual");
	if(res.state != SQL_ROWS || connection_changes(conn) != 0 || res.cursor == NULL) {
		FAIL_TEXT_C("Simple select failed");
	}

	error = cursor_fetch(res.cursor);
	CHECK_C_TEXT(!error && cursor_changes(res.cursor) > 0 && cursor_nrows(res.cursor) > 0, connection_error_message(conn));

	TypeEngine* val = cursor_getValue(res.cursor, 0, 0);
	int len = column_as_int(val);
	CHECK_C(len == 16);

	free_cursor(res.cursor);

	res = connection_execute(conn,"SELECT CAST(-1 AS NUMBER(19,9)) AS LONG_DOUBLE FROM DUAL");
	if(res.state != SQL_ROWS || connection_changes(conn) != 0 || res.cursor == NULL) {
		FAIL_TEXT_C("Simple select failed");
	}
	CHECK_EQUAL_C_STRING("LONG_DOUBLE", cursor_name(res.cursor, 0));

	error = cursor_fetch(res.cursor);
	CHECK_C_TEXT(!error && cursor_changes(res.cursor) > 0 && cursor_nrows(res.cursor) > 0, connection_error_message(conn));
	val = cursor_getValue(res.cursor, 0, (unsigned)cursor_number(res.cursor, "LONG_DOUBLE"));
	len = column_as_int(val);
	CHECK_C(len == -1);

	free_cursor(res.cursor);
	free_connection(conn);
	free_engine(engine);
}

TEST_C(driver_oracle_c, insert_bind_update_select_delete_c) {
	conn_state error;
	char uri[] ="oracle+oracle://BSM_DBA:BSM_DBA_MICH@CBSMOLS1.world/BSM_DBA";

	Engine* engine = create_engine_p(uri);
	Connection* conn = engine_connect(engine);

	struct connection_result res = connection_prepare(conn,
		"INSERT INTO PARAMETROS(CODPAR, VALPAR, SITACT) VALUES(:codpar, :valpar, :sitact)");
	if(res.state != SQL_DONE) {
		FAIL_C();
	}

	Statement* stmt = res.stmt;
	stmt_bind_char(stmt, 0, "H1!", 3);
	stmt_bind_char(stmt, 0, "H2!", 3);
	stmt_bind_char(stmt, 1, "world!", 5);
	stmt_bind_char(stmt, 2, ":)", 2);

	res = connection_step(conn, stmt);
	if(res.state != SQL_DONE) {
		FAIL_C();
	}
	free_statement(stmt);

	res = connection_prepare(conn,"SELECT CODPAR, VALPAR, SITACT FROM PARAMETROS WHERE CODPAR = :codpar AND VALPAR = :valpar AND SITACT = :sitact");
	if(res.state != SQL_DONE ||  res.stmt == NULL) {
		FAIL_TEXT_C("Simple select failed");
	}
	
	stmt = res.stmt;
	stmt_bind_char(stmt, 0, "H2!", 4);
	stmt_bind_char(stmt, 1, "world!", 7);
	stmt_bind_char(stmt, 2, ":)", 3);
	res = connection_step(conn, stmt);
	if(res.state != SQL_ROWS || res.cursor == NULL) {
		FAIL_C();
	}

	error = cursor_fetch(res.cursor);
	CHECK_C_TEXT(!error && cursor_changes(res.cursor) == 1 && cursor_nrows(res.cursor) > 0, connection_error_message(conn));
	char tmp1[4]; column_as_char(cursor_getValue(res.cursor, 0, 0), tmp1, sizeof tmp1);
	char tmp2[8]; column_as_char(cursor_getValue(res.cursor, 0, 1), tmp2, sizeof tmp2);
	char tmp3[4]; column_as_char(cursor_getValue(res.cursor, 0, 2), tmp3, sizeof tmp3);
	CHECK_EQUAL_C_STRING("H2!", tmp1);
	CHECK_EQUAL_C_STRING("world!", tmp2);
	CHECK_EQUAL_C_STRING(":)", tmp3);

	error = connection_rollback(conn);
	if(error != SQL_DONE) {
		FAIL_C();
	}

	free_cursor(res.cursor);
	free_statement(stmt);
	free_connection(conn);
	free_engine(engine);
}