#include <vector>
#include <stdexcept>
#include <cassert>
#include <mutex>
#include <stddef.h>

#define SQLCA_STORAGE_CLASS extern
#define ORACA_STORAGE_CLASS extern
#include <sqlca.h>

#include "driver/oracle/driver_ora_cursor.h"
#include "driver/oracle/cursor.hpp"
#include "inner_driver_oracle.h"
#include "driver/oracle/connection_data.h"
#include "oracle_types.h"
#include "connection/state.h"
#include "driver/oracle/factory.hpp"

driver::oracle::Cursor::Cursor(struct oracle_connection_data arg_conn, std::shared_ptr<struct resource_ora_cursor> arg_cursor) :
	cursor(arg_cursor), conn(arg_conn), _nfields(0U), _ntuples(0U), _changes(0) {}

driver::oracle::Cursor& driver::oracle::Cursor::operator=(const driver::oracle::Cursor& arg) {
	//std::vector<std::shared_ptr<TypeEngine> > _values;
	conn = arg.conn;
	_nfields = arg._nfields;
	_ntuples = arg._ntuples;
	_changes = arg._changes;
	cursor = arg.cursor;
	return *this;	
}

/** The desctructor close the connection
 * Here if fail is not posible recover the cursor then the program is bad
 * die if error
 */
driver::oracle::Cursor::~Cursor() {
	std::call_once(close_cursor_flag, [this](){ close_cursor(); });
}

conn_state driver::oracle::Cursor::open_cursor(void) {
	conn_state state = SQL_DONE;
	state = cursor->open(&conn, _nfields);
	if(state) {
		assert(!"Atempt to open cursor failed");
		throw std::runtime_error("Couldn't open the cursor");
		return state;
	}

	for(unsigned i = 0; i < _nfields; i++) {
		struct ora_database_type ptr;
		state = driver_ora_get_descriptor_column(&conn, i + 1, &ptr);
		if(state) {
			assert(!"Internal error");
			return state;
		}
		assert((size_t)ptr.length > 0);
		_names.push_back(std::string(ptr.name));
		_size.push_back((size_t)ptr.length);
		_type_id.push_back(driver::oracle::TypeFactory::coerced_type(ptr.type));
	}
	return state;
}

conn_state driver::oracle::Cursor::open(void) {
	conn_state state = driver_ora_fields_out_count(&conn, &_nfields);
	std::call_once(open_cursor_flag, [this, &state](){ state = open_cursor();});
	return state;
}

/**
 * \brief fetch one row in memory
 * \warning if this function return error even if retry the fetched row is lost
 * \return conn_state
 */
conn_state driver::oracle::Cursor::fetch(void) {
	conn_state state = SQL_DONE;

	state = cursor->fetch(&conn, &_changes);
	if(state != SQL_DONE && state != SQL_ROWS) {
		assert(!state || !"Invalid operation fetch over cursor");
		return state;
	}

	size_t osize = _values.size();
	_values.resize(osize + _nfields);
	for(unsigned i = 0; i < _nfields; i++) {
		struct ora_database_type ptr;
		state = driver_ora_get_descriptor_column(&conn, i + 1, &ptr);
		if(state) {
			_values.resize(osize);
			return state;
		}
		
		driver::oracle::TypeFactory factory{&ptr};
		_values[osize + i] = factory.factory();
		if(ptr.indicator != -1) { free(ptr.data); }
	}
	_ntuples += sqlca.sqlerrd[2] > 0 ? (unsigned)sqlca.sqlerrd[2] : 0u;
	_changes += sqlca.sqlerrd[2] > 0 ? (unsigned)sqlca.sqlerrd[2] : 0u;
	return state;
}

void driver::oracle::Cursor::close_cursor(void) {
	conn_state state = SQL_DONE;

	state = cursor->close(&conn);
	if(state) {
		assert(!"Atempt to close cursor failed");
		throw std::runtime_error("Couldn't close the cursor");
	}
	cursor.reset(); // free de resource
	assert(cursor.use_count() == 0);
}

conn_state driver::oracle::Cursor::close(void) {
	conn_state state = SQL_DONE;

	std::call_once(close_cursor_flag, [this](){ close_cursor(); });

	return state;
}

TypeEngine* driver::oracle::Cursor::_getValue(unsigned row, unsigned column) const {
	return _values[row * nfields() + column].get();
}