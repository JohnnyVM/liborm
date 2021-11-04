#include <stdlib.h>
#include <stdint.h>

#include "sqlite3.h"

#include "database_params.h"
#include "libdict/dict.h"
#include "libarray/array.h"
#include "status.h"
#include "connection.h"
#include "visibility.h"

#include "open.h"

/** Recompile the statement every time is called its a relative poor performance choice */
STATIC struct orm_status execute_many(struct sqlite_connection* conn, const char* stmt, struct array* params) {
	struct orm_status output = {
		.type = NO_OUTPUT,
		.error = NO_ERROR };

	if(!conn) {
		output.error = INVALID_PARAMETERS;
		return output;
	}

	int check = sqlite3_prepare_v2(conn->database, stmt, -1, &conn->statement, NULL);
	if( check != SQLITE_OK ) {
		output.error = SQLITE3_ERROR;
		output.error_code = check;
	}

	size_t k = !params || !params->length;
	switch(k) {
		case 0:
		for(uintmax_t i = 0; params && i < params->length; i++) {
			// TODO bind parameters
			case 1:
			check = sqlite3_step(conn->statement);
			if(check != SQLITE_DONE && check != SQLITE_ROW) {
				output.error = SQLITE3_ERROR;
				output.error_code = check;
				break;
			}
		}
	}

	if(check == SQLITE_DONE || check != SQLITE_ROW) {
		check = sqlite3_finalize(conn->statement);
		if( check != SQLITE_OK) {
			output.error = SQLITE3_ERROR;
			output.error_code = check;
		}
	}

	return output;
}

/* public */
struct orm_status driver_sqlite_execute_many(void* conn, const char* stmt, struct array* params) {
	return execute_many(conn, stmt, params);
}
