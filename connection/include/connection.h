#ifndef LIBORM_CONNECTION_H
#define LIBORM_CONNECTION_H

#ifndef ORA_PROC
#include <stdbool.h>
#else
typedef unsigned char bool;
#endif

enum connection_error {
	NO_CONNECTION_ERROR = 0,
	UNKNOWN_ERROR = 1,
	DATABASE_ERROR,
	NO_IMPLEMENTED,
	UNSUPPORTED_OPERATION,
	CURSOR_CLOSED,
	NO_MEMORY,
	NO_MORE_ROWS,
};


#ifndef __cplusplus

typedef struct Connection Connection;
typedef struct Cursor Cursor;

#else

class Engine;

/** A Cursor that is representing state from a DBAPI cursor.
 *	Its in charge of handle the memory used
 * */
class Cursor {
	public:
	virtual ~Cursor() {}
	Cursor() {}
	virtual struct connection_state fetch(void) = 0; /**< fetch the default quantity determined by the driver */
	virtual unsigned nfields(void) = 0;
	virtual unsigned nrows(void) = 0;
	virtual unsigned changes(void) = 0; /**< return the number of rows modified, inserted or deleted by the most recently completed INSERT, UPDATE or DELETE statement */
	virtual bool is_open(void) = 0;
	virtual struct connection_state open(void) = 0;
	virtual struct connection_state close(void) = 0;
};

/**
 * AConnection to the DBAPI
 */
class Connection {
	public:
	virtual ~Connection() {};
	Connection(Engine* arg_engine) : engine(arg_engine) {}
	Connection(Connection&) = delete;
	void operator=(const Connection&) = delete;
	virtual struct connection_state open() = 0;
	virtual struct connection_state close() = 0;
	virtual struct connection_state begin() = 0;
	virtual struct connection_state commit() = 0;
	virtual struct connection_state rollback() = 0;
	virtual struct connection_state execute_many(const char* stmt, void* /*struct array *params*/) = 0;
	virtual struct connection_state execute(const char* stmt) = 0;
	//virtual struct connection_state fetch_many() = 0;

	/** \todo database structure */
	/*struct connection_state (*get_columns)(void) = 0;
	struct connection_state (*get_table_id)(void) = 0;
	struct connection_state (*get_column_definition)(void) = 0;*/
	/* etc */
	//const char* error_message(void*) = 0; /**< transfconnection a error code in a message database specific */
	//bool autobegin; /**< The db begin a transacion when connect */
	Engine* engine;
};

#endif

struct connection_state {
	enum connection_error error;
	bool tuples_ok; /**< if ok, connection can be fetched, it doesnt mean some rows have to be returned */
	unsigned changes;
	union {
		Cursor* cursor; /**< No access to this memeber if tuples_ok = false */
	};
};

#define INIT_CONNECTION_STATE {\
	.error = NO_CONNECTION_ERROR,\
	.tuples_ok = false,\
	.changes = 0,\
	.cursor = NULL\
}

#ifdef __cplusplus
extern "C" {
#endif

void free_connection(Connection* conn);
struct connection_state connection_execute_many(Connection* conn, const char* stmt, void*);
struct connection_state connection_execute(Connection* conn, const char* stmt);

struct connection_state cursor_open(Cursor*);
struct connection_state cursor_close(Cursor*);
void free_cursor(Cursor* c);

unsigned cursor_nfields(Cursor *c);
unsigned cursor_ntuples(Cursor *c);
unsigned cursor_changes(Cursor *c);

#ifdef __cplusplus
}
#endif

#endif
