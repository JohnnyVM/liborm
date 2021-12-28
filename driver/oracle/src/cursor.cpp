#include <vector>
#include <stddef.h>

#include "driver/oracle/cursor.hpp"
#include "inner_driver_oracle.h"
#include "driver/oracle/connection_data.h"
#include "oracle_types.h"

driver::oracle::Cursor::Cursor(struct oracle_connection_data* arg_data) :
	data(arg_data), _nfields(0U), _ntuples(0U), _changes(0), _open(false) {}

driver::oracle::Cursor::~Cursor() {
	this->close();
}

conn_error driver::oracle::Cursor::open(void) {
	struct connection_state state = driver_ora_fields_count(data,&_nfields);
	if(state.error) {
		return state.error;
	}

	state = driver_ora_cursor_open(data, _nfields);
	if(state.error == NO_CONNECTION_ERROR) {
		_open = true;
	}

	return state.error;
}

conn_error driver::oracle::Cursor::fetch(void) {
	struct connection_state state = driver_ora_fetch(data, &_changes);
	if(state.error) {
		return state.error;
	}

	struct ora_database_type ptr;
	size_t osize = _values.size();
	_values.resize(osize + _nfields);
	for(unsigned i = 0; i < _nfields; i++) {
		state = driver_ora_get_descriptor_column(data, _nfields + 1, &ptr);
		if(state.error) {
			if(ptr.indicator != -1) { free(ptr.data); }
			_values.resize(osize);
			return state.error;
		}
		//_values[osize + i].reset(ptr);
		if(ptr.indicator != -1) { free(ptr.data); }
	}
	_ntuples++;
	return state.error;
}

conn_error driver::oracle::Cursor::close(void) {
	struct connection_state state = driver_ora_cursor_close(data);
	if(!state.error) {
		_open = false;
	}
	return state.error;
}

