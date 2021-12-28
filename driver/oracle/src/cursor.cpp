#include <vector>
#include <stdexcept>

#include <stddef.h>

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
		conn_error err = this->close();
		assert(!err || !"Atempt to close cursor failed");
	}
}

conn_error driver::oracle::Cursor::open(void) {
	struct connection_state state = driver_ora_fields_count(&conn, &_nfields);
	if(state.error) {
		return state.error;
	}

	state = driver_ora_cursor_open(&conn, _nfields);
	if(!state.error) {
		_is_open = true;
	}

	return state.error;
}

/**
 * \brief fetch one row in memory
 * \warning if this function return error even if retry the fetched row is lost
 * \return conn_error
 */
conn_error driver::oracle::Cursor::fetch(void) {
	struct connection_state state = driver_ora_fetch(&conn, &_changes);
	if(state.error) {
		return state.error;
	}

	size_t osize = _values.size();
	_values.resize(osize + _nfields);
	for(unsigned i = 0; i < _nfields; i++) {
		struct ora_database_type *ptr = (struct ora_database_type *)malloc(sizeof *ptr);
		state = driver_ora_get_descriptor_column(&conn, _nfields + 1, ptr);
		if(state.error) {
			free(ptr);
			_values.resize(osize);
			return state.error;
		}
		
		driver::oracle::TypeFactory factory{ptr};
		TypeEngine* value = factory.factory();
		_values[osize + i].reset(value);
		free_ora_database_type(ptr);
	}
	_ntuples++;
	return state.error;
}

conn_error driver::oracle::Cursor::close(void) {
	struct connection_state state = driver_ora_cursor_close(&conn);
	if(!state.error) {
		_is_open = false;
	}
	return state.error;
}

