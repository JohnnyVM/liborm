#ifndef LIBORM_CONNECTION_CONNECTION_HPP
#define LIBORM_CONNECTION_CONNECTION_HPP

#include <tuple>
#include <memory>
#include <cassert>

#include "connection/statement.h"
#include "connection/types.h"

class Cursor;

/**
 * AConnection to the DBAPI
 */
class Connection {
	public:
	virtual ~Connection() = default;
	Connection& operator=(const Connection&) = delete;
	[[nodiscard]] virtual conn_state close() = 0;
	[[nodiscard]] virtual conn_state begin() = 0;
	[[nodiscard]] virtual conn_state commit() = 0;
	[[nodiscard]] virtual conn_state rollback() = 0;
	[[nodiscard]] virtual std::tuple<std::unique_ptr<Cursor>, conn_state> execute(const Statement& stmt) = 0;
	template<typename T, std::enable_if_t<std::is_convertible<T, std::string>::value, bool> = true>
	[[nodiscard]] inline std::tuple<std::unique_ptr<Cursor>, conn_state> execute(const T& stmt) { return execute(Statement(stmt)); }

	[[nodiscard]] virtual bool is_open() = 0; /**< the connection is open */
	[[nodiscard]] virtual unsigned changes() = 0; /**< list of rows modified by the last statement */
	[[nodiscard]] virtual const char* error_message() = 0; /**< return latest connection error code as message database specific */
};

#endif
