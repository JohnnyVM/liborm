#ifndef LIBORM_DRIVER_POSTGRES_HPP
#define LIBORM_DRIVER_POSTGRES_HPP

#include "engine.h"
#include "connection.h"

#include <libpq-fe.h>

namespace driver {

class Postgres : virtual public Connection {
	public:
	Postgres(Engine* engine);
	~Postgres();
	struct connection_state open(void) override;
	struct connection_state begin(void) override;
	struct connection_state commit(void) override;
	struct connection_state rollback(void) override;
	struct connection_state execute_many(const char*, void* /*struct array *params*/) override;
	struct connection_state execute(const char*) override;

	protected:
	struct connection_state close(void) override;

	private:
	PGconn* pg_conn = nullptr;
	PGresult* pg_res = nullptr;
};

}

#endif
