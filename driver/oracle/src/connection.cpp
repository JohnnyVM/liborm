#include <stdexcept>
#include <system_error>
#include <string>
#include <mutex>
#include <utility>

#include "engine/engine.h"
#include "driver/oracle/cursor.hpp"
#include "driver/oracle/connection.hpp"
#include "connection/connection.h"
#include "inner_driver_oracle.h"

/** The desctructor close the connection
 * Here if fail is not posible recover the connetion then the program is bad
 * die if error
 */
driver::oracle::Connection::~Connection() {
	[[maybe_unused]] conn_state err = close();
}

Connection* driver::oracle::Connection::clone_c(void) {
	driver::oracle::Connection *conn = new driver::oracle::Connection(data);
	*conn = *this;
	return dynamic_cast<Connection*>(conn);
}

conn_state driver::oracle::Connection::close(void) {
	struct connection_result state = INIT_CONNECTION_RESULT;
	std::call_once(close_connection_flag, [&,this]() {
		driver_ora_close(&data);
		assert(!state.state || !"Error at close connection");
	});
	_is_open = false;
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
	struct connection_result state = driver_ora_rollback(&data);
	assert(!state.state || !"Error at rollback transaction");
	return state.state;
}

const char* driver::oracle::Connection::error_message(void) {
	return  driver_ora_short_error_message();
}

std::tuple<std::unique_ptr<Cursor>, conn_state> driver::oracle::Connection::execute(const std::string& stmt) {

	struct connection_result state = driver_ora_execute_many(&data, stmt.c_str(), nullptr);
	if(state.state != SQL_ROWS) {
		return std::tuple<std::unique_ptr<driver::oracle::Cursor>, conn_state>(nullptr, state.state);
	}

	std::unique_ptr<driver::oracle::Cursor> cursor = std::make_unique<driver::oracle::Cursor>(data);
	state.state = cursor->open();
	if(state.state) {
		assert(!"Error at cursor open");
		return std::tuple<std::unique_ptr<driver::oracle::Cursor>, conn_state>(nullptr, state.state);
	}

	state.state = SQL_ROWS;
	_changes += state.changes;
	cursor->_changes += state.changes;
	return std::tuple<std::unique_ptr<driver::oracle::Cursor>, conn_state>(std::move(cursor), state.state);
}

