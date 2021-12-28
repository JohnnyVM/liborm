#include <stdexcept>
#include <system_error>
#include <string>

#include "engine.h"
#include "driver/oracle/cursor.hpp"
#include "driver/oracle/connection.hpp"
#include "connection.h"
#include "inner_driver_oracle.h"

/** The desctructor close the connection */
driver::oracle::Connection::~Connection() {
	this->close();
}

conn_error driver::oracle::Connection::close(void) {
	struct connection_state state = INIT_CONNECTION_STATE;
	state = driver_ora_close(&data);
	return state.error;
}

conn_error driver::oracle::Connection::begin(void) {
	assert(!"TODO");
	return NO_CONNECTION_ERROR;
}

conn_error driver::oracle::Connection::commit(void) {
	struct connection_state state = INIT_CONNECTION_STATE;
	state = driver_ora_commit(&data);
	return state.error;
}

conn_error driver::oracle::Connection::rollback(void) {
	assert(!"TODO");
	return NO_CONNECTION_ERROR;
}

unsigned driver::oracle::Connection::changes(void) {
	assert(!"TODO");
	return 0;
}

bool driver::oracle::Connection::is_open(void) {
	assert(!"TODO");
	return false;
}

std::tuple<Cursor*, conn_error> driver::oracle::Connection::execute(const std::string& stmt) {
	struct connection_state state = INIT_CONNECTION_STATE;
	state = driver_ora_execute_many(&data, stmt.c_str(), nullptr);
	if(!state.error) {
		// TODO open cursor
	}
	return std::tuple<Cursor*, conn_error>(nullptr, state.error);
}

