#ifndef LIBORM_CONNECTION_CONNECTION_HPP
#define LIBORM_CONNECTION_CONNECTION_HPP

#include <tuple>
#include <memory>

#include "connection/types.h"

class Cursor;

/**
 * AConnection to the DBAPI
 */
class Connection {
	public:
	virtual ~Connection() = default;
	Connection& operator=(const Connection&) = delete;
	[[nodiscard]] virtual Connection* clone_c() = 0; /**< warning: clone a engine have a lot of side effects, try not have 2 copy of the same object at the same time */
	[[nodiscard]] virtual conn_state close() = 0;
	[[nodiscard]] virtual conn_state begin() = 0;
	[[nodiscard]] virtual conn_state commit() = 0;
	[[nodiscard]] virtual conn_state rollback() = 0;
	[[nodiscard]] virtual std::tuple<std::unique_ptr<Cursor>, conn_state> execute(const std::string& stmt) = 0;

	[[nodiscard]] virtual bool is_open() = 0; /**< the connection is open */
	[[nodiscard]] virtual unsigned changes() = 0; /**< list of rows modified by the last statement */
	/** \todo database structure */
	/*struct connection_result (*get_columns)(void) = 0;
	struct connection_result (*get_table_id)(void) = 0;
	struct connection_result (*get_column_definition)(void) = 0;*/
	/* etc */
	[[nodiscard]] virtual const char* error_message() = 0; /**< return latest connection error code as message database specific */
	//bool autobegin; /**< The db begin a transacion when connect */
};

#endif
