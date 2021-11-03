#include <stdlib.h>

#include "sqlite3.h"

#include "database_params.h"
#include "libdict/dict.h"
#include "status.h"
#include "connection.h"
#include "visibility.h"

#include "open.h"

/* The most of the functions need to ve declared as static for avoid name conflict*/
STATIC struct orm_status close(struct sqlite_connection* conn) {
	struct orm_status output = {
		.type = NO_OUTPUT,
		.error = NO_ERROR,
	};

	if(!conn) {
		output.error = INVALID_PARAMETERS;
		return output;
	}

	int check = sqlite3_close_v2(conn->database);
	if( check != SQLITE_OK ) {
		output.error = SQLITE3_ERROR;
		output.error_code = check;
		return output;
	}
	free(conn);

	return output;
}

/* public */
struct orm_status driver_sqlite_close(void* conn) {
	return close(conn);
}

