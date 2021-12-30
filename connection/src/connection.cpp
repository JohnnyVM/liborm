#include <string>

#include "connection/types.h"
#include "connection/connection.hpp"
#include "connection/state.h"

extern "C" {

struct connection_result connection_execute(Connection* conn, const char* stmt) {
	struct connection_result state = INIT_CONNECTION_RESULT;
	auto [cursor, err] = conn->execute((std::string)stmt);
	if(err) {
		state.state = err;
		return state;
	}

	state.changes = conn->changes();
	state.cursor = cursor->clone_c();
	return state;
}

void free_connection(Connection* conn) {
	delete conn;
}

}
