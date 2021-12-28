#ifndef LIBORM_DRIVER_ORACLE_CONNECTION_HPP
#define LIBORM_DRIVER_ORACLE_CONNECTION_HPP

#include <memory>

#include "connection.h"
#include "driver/oracle/connection_data.h"

using PConnection = Connection;
using PCursor = Cursor;

namespace driver::oracle {

class Connection : virtual public PConnection {
	public:
	Connection(struct oracle_connection_data conn) : data(conn), _changes(0U), _is_open(false) {}
	~Connection();
	conn_error close(void) override;
	[[nodiscard]] conn_error begin(void) override;
	[[nodiscard]] conn_error commit(void) override;
	[[nodiscard]] conn_error rollback(void) override;
	[[nodiscard]] virtual std::tuple<PCursor*, conn_error> execute(const std::string& stmt) override;

	[[nodiscard]] bool is_open() override { return _is_open; }; /**< the connection is open */
	[[nodiscard]] unsigned changes() override { return _changes;};

	private:
	struct oracle_connection_data data;
	unsigned _changes;
	bool _is_open;
};

}

#endif

