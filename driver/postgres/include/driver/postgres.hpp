#ifndef LIBORM_DRIVER_POSTGRES_HPP
#define LIBORM_DRIVER_POSTGRES_HPP

#include "engine/engine.h"
#include "connection/connection.h"

#include <libpq-fe.h>

namespace driver {

class Postgres : virtual public Connection {
	public:
	Postgres(Engine* engine);
	~Postgres();
	struct connection_result open(void) override;
	struct connection_result begin(void) override;
	struct connection_result commit(void) override;
	struct connection_result rollback(void) override;
	struct connection_result execute_many(const char*, void* /*struct array *params*/) override;
	struct connection_result execute(const char*) override;

	protected:
	struct connection_result close(void) override;

	private:
	PGconn* pg_conn = nullptr;
	PGresult* pg_res = nullptr;
};

}

#endif
