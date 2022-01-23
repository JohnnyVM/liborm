#include <string>

#include "liborm/connection/types.h"
#include "connection/connection.hpp"
#include "liborm/connection/state.h"
#include "connection/cursor.hpp"
#include "liborm/connection/statement.h"

extern "C" {

conn_state connection_close(Connection* conn) {
	return conn->close();
}

conn_state connection_begin(Connection* conn) {
	return conn->begin();
}

conn_state connection_commit(Connection* conn) {
	return conn->commit();
}

conn_state connection_rollback(Connection* conn) {
	return conn->rollback();
}

struct connection_result connection_execute(Connection* conn, const char* const stmt) {
	struct connection_result state = INIT_CONNECTION_RESULT;
	auto [cursor, err] = conn->execute((std::string)stmt);
	if(err != SQL_DONE && err != SQL_ROWS) {
		state.state = err;
		return state;
	}

	state.state = err;
	state.changes = conn->changes();
	state.cursor = cursor.release();
	return state;
}

void free_connection(Connection* conn) {
	delete conn;
}

const char* connection_error_message(Connection* const conn) {
	return conn->error_message();
}

unsigned connection_changes(Connection* const conn) {
	return conn->changes();
}

struct connection_result connection_prepare([[maybe_unused]] Connection* conn, const char* stmt) {
	struct connection_result state = INIT_CONNECTION_RESULT;
	state.stmt = new Statement(stmt);
	return state;
}

struct connection_result connection_step(Connection* conn, Statement* stmt) {
	struct connection_result state = INIT_CONNECTION_RESULT;
	std::vector<std::vector<std::shared_ptr<const TypeEngine>>>rows;
	rows.emplace_back(stmt->params);
	auto [cursor, err] = conn->execute(stmt->statement, rows);
	if(err != SQL_DONE && err != SQL_ROWS) {
		state.state = err;
		return state;
	}

	state.state = err;
	state.changes = conn->changes();
	if(err == SQL_ROWS) {
		state.cursor = cursor.release();
	}
	return state;
}

}
