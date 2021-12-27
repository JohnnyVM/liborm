#ifndef LIBORM_DRIVER_ORACLE_CONNECTION_HPP
#define LIBORM_DRIVER_ORACLE_CONNECTION_HPP

#include "connection.h"
#include "driver/oracle/connection_data.h"

using PConnection = Connection;

namespace driver::oracle {

class Connection : virtual public PConnection {
	public:
	Connection(struct oracle_connection_data conn) : data(conn) {}
	~Connection();
	[[nodiscard]] conn_error close(void) override;
	[[nodiscard]] conn_error begin(void) override;
	[[nodiscard]] conn_error commit(void) override;
	[[nodiscard]] conn_error rollback(void) override;
	[[nodiscard]] virtual std::tuple<Cursor*, conn_error> execute(const char* stmt) override;

	private:
	struct oracle_connection_data data;
};

}

#endif

