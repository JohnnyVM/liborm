#ifndef LIBORM_CONNECTION_STATE_H
#define LIBORM_CONNECTION_STATE_H

#include <stdlib.h>

#include "connection/types.h"
#include "connection/cursor_c.h"

#if !defined(ORA_PROC)
#include <stdbool.h>
#elif
typedef unsigned char bool;
#endif

struct connection_state {
	enum connection_error error;
	bool tuples_ok; /**< if ok, connection can be fetched, it doesnt mean some rows have to be returned */
	unsigned changes;
	Cursor* cursor; /**< No access to this memeber if tuples_ok = false */
};

#define INIT_CONNECTION_STATE {\
	.error = NO_CONNECTION_ERROR,\
	.tuples_ok = false,\
	.changes = 0,\
	.cursor = NULL\
}

#endif
