#ifndef LIBORM_DRIVER_ORACLE_CONNECTION_HPP
#define LIBORM_DRIVER_ORACLE_CONNECTION_HPP

#include <memory>
#include <mutex>

#include "connection/connection.h"
#include "driver/oracle/connection_data.h"

using PConnection = Connection;
using PCursor = Cursor;

namespace driver::oracle {

class Connection final : virtual public PConnection {
	public:
	Connection(struct oracle_connection_data conn) : data(conn), _changes(0U), _is_open(true) {}
	~Connection();
	Connection& operator=(Connection& arg) { data = arg.data; _changes = arg._changes; _is_open = arg._is_open; return *this; }
	[[nodiscard]] PConnection* clone_c() override; /**< warning: clone a engine have a lot of side effects, try not have 2 copy of the same object at the same time */
	[[nodiscard]] conn_state close(void) override;
	[[nodiscard]] conn_state begin(void) override;
	[[nodiscard]] conn_state commit(void) override;
	[[nodiscard]] conn_state rollback(void) override;
	[[nodiscard]] virtual std::tuple<std::unique_ptr<PCursor>, conn_state> execute(const std::string& stmt) override;

	[[nodiscard]] bool is_open() override { return _is_open; }; /**< the connection is open */
	[[nodiscard]] unsigned changes() override { return _changes;};
	[[nodiscard]] const char* error_message(); /**< latest connection error message, no thread safe */

	private:
	struct oracle_connection_data data;
	unsigned _changes;
	bool _is_open;
	std::once_flag close_connection_flag;
};

}

#endif

