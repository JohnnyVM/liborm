#include <vector>
#include <stdexcept>
#include <cassert>
#include <mutex>
#include <stddef.h>

#define SQLCA_STORAGE_CLASS extern
#define ORACA_STORAGE_CLASS extern
#include <sqlca.h>

#include "driver/oracle/cursor.hpp"
#include "inner_driver_oracle.h"
#include "driver/oracle/connection_data.h"
#include "oracle_types.h"
#include "connection/state.h"
#include "driver/oracle/factory.hpp"

driver::oracle::Cursor::Cursor(struct oracle_connection_data arg_conn) :
	conn(arg_conn), _nfields(0U), _ntuples(0U), _changes(0), _is_open(false) {}

driver::oracle::Cursor& driver::oracle::Cursor::operator=(const driver::oracle::Cursor& arg) {
	//std::vector<std::shared_ptr<TypeEngine> > _values;
	conn = arg.conn;
	_nfields = arg._nfields;
	_ntuples = arg._ntuples;
	_changes = arg._changes;
	_is_open = _is_open;
	return *this;	
}

/** The desctructor close the connection
 * Here if fail is not posible recover the cursor then the program is bad
 * die if error
 */
driver::oracle::Cursor::~Cursor() {
	std::call_once(close_cursor_flag, [this](){ close_cursor(); });
}

conn_state driver::oracle::Cursor::open(void) {
	struct connection_result state = driver_ora_fields_count(&conn, &_nfields);

	return state.state;
}

void driver::oracle::Cursor::open_cursor(void) {
	struct connection_result state = INIT_CONNECTION_RESULT;
	m.lock();
	state = driver_ora_cursor_open(&conn, _nfields);
	if(!state.state) {
		_is_open = true;
	} else {
		m.unlock();
		assert(!"Atempt to open cursor failed");
		throw std::runtime_error("Couldn't open the cursor");
	}
}

/**
 * \brief fetch one row in memory
 * \warning if this function return error even if retry the fetched row is lost
 * \return conn_state
 */
conn_state driver::oracle::Cursor::fetch(void) {
	struct connection_result state = INIT_CONNECTION_RESULT;

	std::call_once(open_cursor_flag, [this](){ open_cursor(); });
	if(not _is_open) {
		assert(!"Atempt to fetch closed cursor");
		return SQL_MISUSE;
	}

	state = driver_ora_fetch(&conn, &_changes);
	if(state.state != SQL_DONE && state.state != SQL_ROWS) {
		assert(!state.state || !"Invalid operation fetch over cursor");
		return state.state;
	}
	if(state.state == SQL_DONE) {
		_is_open = false;
	}
	size_t osize = _values.size();
	_values.resize(osize + _nfields);
	for(unsigned i = 0; i < _nfields; i++) {
		struct ora_database_type ptr;
		state = driver_ora_get_descriptor_column(&conn, i + 1, &ptr);
		if(state.state) {
			_values.resize(osize);
			return state.state;
		}
		
		driver::oracle::TypeFactory factory{&ptr};
		_values[osize + i] = factory.factory();
		if(ptr.indicator != -1) { free(ptr.data); }
	}
	_ntuples += sqlca.sqlerrd[2];
	_changes += sqlca.sqlerrd[2];
	return state.state;
}

void driver::oracle::Cursor::close_cursor(void) {
	struct connection_result state = INIT_CONNECTION_RESULT;

	if(_is_open) {
		state = driver_ora_cursor_close(&conn);
		m.unlock(); // doesnt matter 
		if(!state.state) {
			_is_open = false;
		} else { // this is a very bad situation
			assert(!"Atempt to close cursor failed");
			throw std::runtime_error("Couldn't close the cursor");
		}
	}
}

conn_state driver::oracle::Cursor::close(void) {
	struct connection_result state = INIT_CONNECTION_RESULT;

	std::call_once(close_cursor_flag, [this](){ close_cursor(); });

	return state.state;
}

PCursor* driver::oracle::Cursor::clone_c() {
	driver::oracle::Cursor* c = new driver::oracle::Cursor(conn);
	*c = *this;
	return dynamic_cast<PCursor*>(c);
}

orm::TypeEngine* driver::oracle::Cursor::_getValue(unsigned row, unsigned column) {
	return _values[row * nfields() + column].get();
}