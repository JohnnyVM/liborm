#include <cassert>

#include "connection/cursor.hpp"
#include "connection/state.h"
#include "type/engine.h"

TypeEngine* Cursor::getValue(unsigned row, unsigned column) {
	assert(row < nrows() and column < nfields()); // out of index
	return _getValue(row, column);
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

void free_cursor(Cursor* const c) {
	delete c;
}

TypeEngine* cursor_getValue(Cursor* const c, unsigned row, unsigned column){
	return c->getValue(row, column);
}

}
