#ifndef LIBORM_DRIVER_ORACLE_HPP
#define LIBORM_DRIVER_ORACLE_HPP

#include "engine.h"
#include "connection.h"
#include "driver/oracle/connection_data.h"
#include "driver/oracle/cursor.hpp"

namespace driver {

class Oracle : virtual public Connection {
	public:
	Oracle(Engine* engine);
	~Oracle();
	struct connection_state open(void) override;
	struct connection_state commit(void) override;
	struct connection_state rollback(void) override;
	struct connection_state begin(void) override;
	struct connection_state execute_many(const char* stmt, void* /*struct array *params*/) override;
	struct connection_state execute(const char* stmt) override;
	struct connection_state close(void) override;

	private:
	struct oracle_connection_data data;
	friend class driver::oracle::Cursor;
};

}

#endif
