#include <stdexcept>
#include <system_error>
#include <string>

#include "engine.h"
#include "driver/oracle/cursor.hpp"
#include "driver/oracle/connection.hpp"
#include "connection.h"
#include "inner_driver_oracle.h"

/** The desctructor close the connection
 * Here if fail is not posible recover the connetion then the program is bad
 * die if error
 */
driver::oracle::Connection::~Connection() {
	if(_is_open) {
		conn_error err = this->close();
		assert(!err || !"Couldn't close the connection");
	}
}

conn_error driver::oracle::Connection::close(void) {
	struct connection_state state = driver_ora_close(&data);
	return state.error;
}

conn_error driver::oracle::Connection::begin(void) {
	assert(!"TODO");
	return NO_CONNECTION_ERROR;
}

conn_error driver::oracle::Connection::commit(void) {
	struct connection_state state = driver_ora_commit(&data);
	return state.error;
}

conn_error driver::oracle::Connection::rollback(void) {
	assert(!"TODO");
	return NO_CONNECTION_ERROR;
}

std::tuple<Cursor*, conn_error> driver::oracle::Connection::execute(const std::string& stmt) {
	_changes = 0;

	struct connection_state state = driver_ora_execute_many(&data, stmt.c_str(), nullptr);
	if(state.error) {
		return std::tuple<Cursor*, conn_error>(nullptr, state.error);
	}
		
	Cursor* cursor = new driver::oracle::Cursor(data);
	state.error = cursor->open();
	if(state.error) {
		delete cursor;
		return std::tuple<Cursor*, conn_error>(nullptr, state.error);
	}

	cursor->_changes = _changes = state.changes;
	return std::tuple<Cursor*, conn_error>(cursor, state.error);
}

