#include "connection/types.h"
#include "connection/connection.hpp"
#include "connection/state.h"

extern "C" {

struct connection_state connection_execute(Connection* conn, const char* stmt) {
	struct connection_state state = INIT_CONNECTION_STATE;
	auto [cursor, err] = conn->execute(stmt);
	if(err) {
		state.error = err;
		return state;
	}

	state.changes = conn->changes();
	state.cursor = cursor;
	return state;
}

void free_connection(Connection* conn) {
	delete conn;
}

}
