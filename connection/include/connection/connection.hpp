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
	void operator=(const Connection&) = delete;
	virtual conn_error close() = 0;
	[[nodiscard]] virtual conn_error begin() = 0;
	[[nodiscard]] virtual conn_error commit() = 0;
	[[nodiscard]] virtual conn_error rollback() = 0;
	[[nodiscard]] virtual std::tuple<Cursor*, conn_error> execute(const std::string& stmt) = 0;

	[[nodiscard]] virtual bool is_open() = 0; /**< the connection is open */
	[[nodiscard]] virtual unsigned changes() = 0; /**< list of rows modified by the last statement */
	/** \todo database structure */
	/*struct connection_state (*get_columns)(void) = 0;
	struct connection_state (*get_table_id)(void) = 0;
	struct connection_state (*get_column_definition)(void) = 0;*/
	/* etc */
	//const char* error_message(void*) = 0; /**< transfconnection a error code in a message database specific */
	//bool autobegin; /**< The db begin a transacion when connect */
};

#endif
