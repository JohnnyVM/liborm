#include "sqlite3.h"

#include "database_params.h"
#include "libdict/dict.h"
#include "status.h"
#include "connection.h"
#include "visibility.h"

#include "open.h"

/* The most of the functions need to ve declared as static for avoid name conflict*/
STATIC const char* error_message(struct sqlite_connection* db) {
	return sqlite3_errmsg(db->database);
}

/* public */
const char* driver_sqlite_error_message(void* db) {
	struct sqlite_connection *conn = db;
	return error_message(conn);
}

