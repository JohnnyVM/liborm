#ifndef LIBORM_CONNECTION_CONNECTION_HPP
#define LIBORM_CONNECTION_CONNECTION_HPP

#include <tuple>

#include "connection/types.h"

class Cursor;

/**
 * AConnection to the DBAPI
 */
class Connection {
	public:
	virtual ~Connection() {};
	Connection(const Connection&) = delete;
	void operator=(const Connection&) = delete;
	virtual conn_error_t changes() = 0; /**< list of rows modified by the last statement */
	virtual conn_error_t close() = 0;
	virtual conn_error_t begin() = 0;
	virtual conn_error_t commit() = 0;
	virtual conn_error_t rollback() = 0;
	virtual std::tuple<Cursor*, conn_error_t> execute(const char* stmt) = 0;

	/** \todo database structure */
	/*struct connection_state (*get_columns)(void) = 0;
	struct connection_state (*get_table_id)(void) = 0;
	struct connection_state (*get_column_definition)(void) = 0;*/
	/* etc */
	//const char* error_message(void*) = 0; /**< transfconnection a error code in a message database specific */
	//bool autobegin; /**< The db begin a transacion when connect */
};

#endif
