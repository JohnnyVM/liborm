#include <cassert>

#include "connection/cursor.hpp"
#include "liborm/connection/state.h"
#include "liborm/type/engine.h"

TypeEngine* Cursor::getValue(unsigned row, unsigned column) const {
	assert(row < nrows() and column < nfields()); // out of index
	return _getValue(row, column);
}

const std::string& Cursor::name(unsigned pos) const {
	assert(pos < nfields()); // out of index
	return _names.at(pos);
}

int Cursor::number(const std::string& _name) const {
	for(size_t i = 0; i < _names.size(); i++) {
		if(_names[i] == _name) {
			return (int)i;
		}
	}
	assert(!"Column name not found"); // out of index
	return -1;
}

extern "C" {

conn_state cursor_open(Cursor* const c) {
	return c->open();
}

conn_state cursor_close(Cursor* const c) {
	return c->close();
}

conn_state cursor_fetch(Cursor* const c) {
	return c->fetch();
}

unsigned cursor_nrows(Cursor* const c) {
	return c->nrows();
}

unsigned cursor_nfields(Cursor* const c) {
	return c->nfields();
}

unsigned cursor_changes(Cursor* const c) {
	return c->changes();
}

const char* cursor_name(Cursor* const c, unsigned pos) {
	return (char*)c->name(pos).c_str();
}

int cursor_number(Cursor* const c, const char* const name) {
	return c->number(std::string(name));

}

void free_cursor(Cursor* const c) {
	delete c;
}

TypeEngine* cursor_getValue(Cursor* const c, unsigned row, unsigned column) {
	return c->getValue(row, column);
}

void cleanup_cursor(Cursor** const c) {
	if(c != nullptr) {
		free_cursor(*c);
	}
}

}
