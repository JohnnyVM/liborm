#include <vector>
#include <stdexcept>
#include <cassert>

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

/** The desctructor close the connection
 * Here if fail is not posible recover the cursor then the program is bad
 * die if error
 */
driver::oracle::Cursor::~Cursor() {
	if(_is_open) {
		conn_state err = this->close();
		assert(!err);
	}
}

conn_state driver::oracle::Cursor::open(void) {
	struct connection_result state = driver_ora_fields_count(&conn, &_nfields);
	if(state.state) {
		return state.state;
	}

	state = driver_ora_cursor_open(&conn, _nfields);
	if(!state.state) {
		_is_open = true;
	} else {
		assert(!state.state || !"Atempt to open cursor failed");
	}

	return state.state;
}

/**
 * \brief fetch one row in memory
 * \warning if this function return error even if retry the fetched row is lost
 * \return conn_state
 */
conn_state driver::oracle::Cursor::fetch(void) {
	struct connection_result state = driver_ora_fetch(&conn, &_changes);
	if(state.state) {
		assert(!state.state || !"Invalid operation fetch over cursor");
		return state.state;
	}

	size_t osize = _values.size();
	_values.resize(osize + _nfields);
	for(unsigned i = 0; i < _nfields; i++) {
		struct ora_database_type *ptr = (struct ora_database_type *)malloc(sizeof *ptr);
		state = driver_ora_get_descriptor_column(&conn, i + 1, ptr);
		if(state.state) {
			free(ptr);
			_values.resize(osize);
			return state.state;
		}
		
		driver::oracle::TypeFactory factory{ptr};
		TypeEngine* value = factory.factory();
		_values[osize + i].reset(value);
		free_ora_database_type(ptr);
	}
	_ntuples += sqlca.sqlerrd[2];
	return state.state;
}

conn_state driver::oracle::Cursor::close(void) {
	struct connection_result state = driver_ora_cursor_close(&conn);
	if(!state.state) {
		_is_open = false;
	} else {
		assert(!state.state || !"Atempt to close cursor failed");
	}
	return state.state;
}

