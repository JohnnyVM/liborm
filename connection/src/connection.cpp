#include <string>

#include "connection/types.h"
#include "connection/connection.hpp"
#include "connection/state.h"
#include "connection/cursor.hpp"

extern "C" {

conn_state connection_close(Connection* const conn) {
	return conn->close();
}

conn_state connection_begin(Connection* const conn) {
	return conn->begin();
}

conn_state connection_commit(Connection* const conn) {
	return conn->commit();
}

conn_state connection_rollback(Connection* const conn) {
	return conn->rollback();
}

struct connection_result connection_execute(Connection* const conn, const char* const stmt) {
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

void free_connection(Connection* const conn) {
	delete conn;
}

const char* connection_error_message(Connection* const conn) {
	return conn->error_message();
}

unsigned connection_changes(Connection* const conn) {
	return conn->changes();
}

}
