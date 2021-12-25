#include <vector>
#include <stddef.h>

#include "driver/oracle/cursor.hpp"
#include "inner_driver_oracle.h"
#include "driver/oracle/connection_data.h"

driver::oracle::Cursor::Cursor(struct oracle_connection_data* arg_data) :
	data(arg_data), _nfields(0U), _ntuples(0U), _changes(0), _open(false) {}

driver::oracle::Cursor::~Cursor() {
	this->close();
}

struct connection_state driver::oracle::Cursor::open(void) {
	struct connection_state state = driver_ora_fields_count(data,&_nfields);
	if(state.error) {
		return state;
	}

	state = driver_ora_cursor_open(data, _nfields);
	if(state.error == NO_CONNECTION_ERROR) {
		_open = true;
	}

	return state;
}

struct connection_state driver::oracle::Cursor::fetch(void) {
	struct connection_state state = driver_ora_fetch(data, &_changes);
	if(state.error) {
		return state;
	}

	TypeEngine *ptr;
	size_t osize = _values.size();
	_values.resize(osize + _nfields);
	for(unsigned i = 0; i < _nfields; i++) {
		state = driver_ora_get_descriptor_column(data, _nfields + 1, &ptr);
		if(state.error) {
			_values.resize(osize);
			return state;
		}
		_values[osize + i].reset(ptr);
	}
	_ntuples++;
	return state;
}

struct connection_state driver::oracle::Cursor::close(void) {
	_open = false;
	return driver_ora_cursor_close(data);
}

