#include "connection.h"

extern "C" {

struct connection_state connection_execute_many(Connection* conn, const char* stmt, void* params) {
	return conn->execute_many(stmt, params);
}

struct connection_state connection_execute(Connection* conn, const char* stmt) {
	return conn->execute(stmt);
}

void free_connection(Connection* conn) {
	delete conn;
}

}
