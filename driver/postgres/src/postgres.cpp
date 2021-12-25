#include <string>

#include "driver/postgres.hpp"
#include "engine.h"
#include "connection.h"
#include "driver/postgres.hpp"

#include <libpq-fe.h>

driver::Postgres::Postgres(Engine* engine) : Connection(engine) {}

driver::Postgres::~Postgres() {
	PQclear(pg_res);
	this->close();
}

struct connection_state driver::Postgres::open(void) {
	struct connection_state state = INIT_CONNECTION_STATE;

	char *s_port = (char*)std::to_string(engine->port).c_str();
	if(engine->port == 0) {
		s_port = NULL;
	}

	pg_conn = PQsetdbLogin(
			engine->host.c_str(),
			s_port,
			NULL, // command line options
			NULL, // ignored
			engine->resource.c_str(),
			engine->user.c_str(),
			engine->password.c_str()
	);
	if (PQstatus(pg_conn) != CONNECTION_OK) {
		state.error = DATABASE_ERROR;
	}

	return state;
}

struct connection_state driver::Postgres::close(void) {
	struct connection_state state = INIT_CONNECTION_STATE;
	PQfinish(pg_conn);
	return state;
}

struct connection_state driver::Postgres::begin(void) {
	return execute("BEGIN");
}

struct connection_state driver::Postgres::commit(void) {
	return execute("COMMIT");
}

struct connection_state driver::Postgres::rollback(void) {
	return execute("ROLLBACK");
}

struct connection_state driver::Postgres::execute_many(const char* stmt, void* /*struct array *params*/) {
	struct connection_state state = INIT_CONNECTION_STATE;
	if(stmt == (std::string)"") {
		return state;
	}
	return state;
}

struct connection_state driver::Postgres::execute(const char* stmt) {
	struct connection_state state = INIT_CONNECTION_STATE;

	if (PQresultStatus(pg_res) == PGRES_TUPLES_OK) {
		// warning?
		PQclear(pg_res);
	}

	pg_res = PQexec(pg_conn, stmt);

	if (PQresultStatus(pg_res) == PGRES_TUPLES_OK) {
		state.tuples_ok = true;
		return state;
	}

	if (PQresultStatus(pg_res) != PGRES_COMMAND_OK) {
		state.error = DATABASE_ERROR;
	}

	PQclear(pg_res);
	return state;
}
