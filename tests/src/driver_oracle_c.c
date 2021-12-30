#include "connection/connection.h"
#include "engine/engine.h"

#include "CppUTest/TestHarness_c.h"

TEST_C(driver_oracle_c, select_number_16_c)
{
	conn_state error;
	char uri[] ="oracle+oracle://BSM_DBA:BSM_DBA_MICH@QBSMOLS2.world/BSM_DBA";

	Engine* engine = create_engine_p(uri);
	Connection* conn = engine_connect(engine);

	struct connection_result res = connection_execute(conn,"select 16 from dual");
	if(res.state != SQL_ROWS || connection_changes(conn) != 0 || res.cursor == NULL) {
		FAIL_TEXT_C("Sinmple select failed");
	}

	error = cursor_fetch(res.cursor);
	CHECK_C_TEXT(!error && cursor_changes(res.cursor) > 0 && cursor_nrows(res.cursor) > 0, connection_error_message(conn));

	free_engine(engine);
	free_connection(conn);
	free_cursor(res.cursor);
}

