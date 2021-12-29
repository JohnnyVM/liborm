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
		conn_state err = this->close();
		assert(!err || !"Couldn't close the connection");
	}
}

conn_state driver::oracle::Connection::close(void) {
	struct connection_result state = driver_ora_close(&data);
	assert(!state.state || !"Error at close connection");
	return state.state;
}

conn_state driver::oracle::Connection::begin(void) {
	assert(!"TODO");
	return SQL_DONE;
}

conn_state driver::oracle::Connection::commit(void) {
	struct connection_result state = driver_ora_commit(&data);
	assert(!state.state || !"Error at commit");
	return state.state;
}

conn_state driver::oracle::Connection::rollback(void) {
	assert(!"TODO");
	return SQL_DONE;
}

const char* driver::oracle::Connection::error_message(void) {
	return  driver_ora_short_error_message();
}

std::tuple<Cursor*, conn_state> driver::oracle::Connection::execute(const std::string& stmt) {
	_changes = 0;

	struct connection_result state = driver_ora_execute_many(&data, stmt.c_str(), nullptr);
	if(state.state != SQL_ROWS) {
		return std::tuple<Cursor*, conn_state>(nullptr, state.state);
	}
		
	Cursor* cursor = new driver::oracle::Cursor(data);
	state.state = cursor->open();
	if(state.state) {
		assert(!"Error at cursor open");
		delete cursor;
		return std::tuple<Cursor*, conn_state>(nullptr, state.state);
	}

	state.state = SQL_ROWS;
	cursor->_changes = _changes = state.changes;
	return std::tuple<Cursor*, conn_state>(cursor, state.state);
}

