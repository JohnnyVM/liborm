#include <stdlib.h>

#include "sqlite3.h"

#include "database_params.h"
#include "libdict/dict.h"
#include "status.h"
#include "connection.h"
#include "visibility.h"

#include "open.h"

/* The most of the functions need to ve declared as static for avoid name conflict*/
STATIC struct orm_status open(struct database_params* db_params) {
	struct orm_status output = {
		.type = SQLITE3_CONNECTION,
		.error = NO_ERROR,
		.connection = malloc(sizeof(struct sqlite_connection)) };
	int check;
	check = sqlite3_open_v2(db_params->database, output.connection, db_params->flags, NULL);
	if( check != SQLITE_OK ) {
		free(output.connection);
		output.error = SQLITE3_ERROR;
		output.error_code = check;
	}

	return output;
}

/* public */
struct orm_status driver_sqlite_open(struct database_params* db_params) {
	return open(db_params);
}
