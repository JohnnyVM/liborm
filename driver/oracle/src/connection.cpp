#include <stdexcept>
#include <system_error>
#include <string>
#include <memory>
#include <optional>
#include <vector>

#include "liborm/utils/acbuffer.hpp"
#include "engine/engine.h"
#include "driver/oracle/cursor.hpp"
#include "driver/oracle/factory.hpp"
#include "driver/oracle/connection.hpp"
#include "connection/connection.h"
#include "inner_driver_oracle.h"
#include "driver/oracle/driver_ora_cursor.h"

/* debatable implementation */
static acbuffer<struct resource_ora_cursor> gora_cursors = {
	INIT_ORA_CURSOR(0),
	INIT_ORA_CURSOR(1)};

/** The desctructor close the connection
 * Here if fail is not posible recover the connetion then the program is bad
 * die if error
 */
driver::oracle::Connection::~Connection() {
	[[maybe_unused]] conn_state err = close();
}

conn_state driver::oracle::Connection::close(void) {
	conn_state state = SQL_DONE;
	std::call_once(close_connection_flag, [&,this]() {
		driver_ora_close(&data);
		assert(!state || !"Error at close connection");
	});
	_is_open = false;
	return state;
}

conn_state driver::oracle::Connection::begin(void) {
	assert(!"TODO");
	return SQL_DONE;
}

conn_state driver::oracle::Connection::commit(void) {
	conn_state state = driver_ora_commit(&data);
	assert(!state || !"Error at commit");
	return state;
}

conn_state driver::oracle::Connection::rollback(void) {
	conn_state state = driver_ora_rollback(&data);
	assert(!state || !"Error at rollback transaction");
	return state;
}

const char* driver::oracle::Connection::error_message(void) {
	return  driver_ora_short_error_message();
}

std::tuple<std::unique_ptr<Cursor>, conn_state> driver::oracle::Connection::execute(const std::string& stmt, std::vector<std::vector<std::shared_ptr<const TypeEngine>>>list) {
	struct connection_result state;
	unsigned nout_params;
	std::optional<std::shared_ptr<struct resource_ora_cursor>>oracle_cursor = gora_cursors.get();
	if(not oracle_cursor.has_value()) {
		return std::tuple<std::unique_ptr<driver::oracle::Cursor>, conn_state>(nullptr, SQL_MAXOPENCURSORS);
	}

	conn_state err = oracle_cursor.value().get()->prepare(&data, stmt.c_str());
	if(err != SQL_DONE) {
		return std::tuple<std::unique_ptr<driver::oracle::Cursor>, conn_state>(nullptr, err);
	}

	err = driver_ora_fields_in_count(&data, &nout_params);
	if(err != SQL_DONE) {
		return std::tuple<std::unique_ptr<driver::oracle::Cursor>, conn_state>(nullptr, err);
	}

#ifndef NDEBUG
{
	assert(nout_params == 0 || (nout_params > 0 && list.size() > 0));
	for(std::vector<std::shared_ptr<const TypeEngine>> el : list) {
		assert(nout_params == el.size());
	}
}
#endif

	_changes = 0;
	if(list.size() <= 0) {
		std::vector<std::shared_ptr<const TypeEngine>>row;
		list.emplace_back(row);
	}
	for(std::vector<std::shared_ptr<const TypeEngine>> row : list) {
		for(unsigned i = 1; i <= nout_params; i++) {
			std::unique_ptr<struct ora_database_type, decltype(&free_ora_database_type)> tptr = bind_param(row.at(i - 1));
			err = driver_ora_set_descriptor_input(&data, i, tptr.get());
			if(err != SQL_DONE) {
				return std::tuple<std::unique_ptr<driver::oracle::Cursor>, conn_state>(nullptr, err);
			}
		}
		state = oracle_cursor.value().get()->execute(&data);
		_changes += state.changes;
		if(state.state != SQL_ROWS) {
			return std::tuple<std::unique_ptr<driver::oracle::Cursor>, conn_state>(nullptr, state.state);
		}
	}

	std::unique_ptr<driver::oracle::Cursor> cursor = std::make_unique<driver::oracle::Cursor>(data, oracle_cursor.value());
	state.state = cursor->open();
	if(state.state) {
		assert(!"Error at cursor open");
		return std::tuple<std::unique_ptr<driver::oracle::Cursor>, conn_state>(nullptr, state.state);
	}

	state.state = SQL_ROWS;
	cursor->_changes += state.changes;
	return std::tuple<std::unique_ptr<driver::oracle::Cursor>, conn_state>(std::move(cursor), state.state);
}

