#ifndef LIBORM_CONNECTION_STATE_H
#define LIBORM_CONNECTION_STATE_H

#include <stdlib.h>

#include "liborm/connection/statement.h"
#include "liborm/connection/types.h"
#include "connection/cursor_c.h"

struct connection_result {
	enum connection_state state;
	unsigned changes;
	union {
		Statement* stmt;
		Cursor* cursor; /**< No access to this memeber if state != SQL_ROWS */
	};
};

#define INIT_CONNECTION_RESULT {\
	.state = SQL_DONE,\
	.changes = 0,\
	.cursor = NULL\
}

#endif
