#include "connection/cursor.hpp"
#include "connection/state.h"

extern "C" {

conn_state cursor_open(Cursor* c) {
	return c->open();
}

conn_state cursor_close(Cursor* c) {
	return c->close();
}

conn_state cursor_fetch(Cursor* c) {
	return c->fetch();
}

unsigned cursor_nrows(Cursor* c) {
	return c->nrows();
}

unsigned cursor_nfields(Cursor* c) {
	return c->nfields();
}

unsigned cursor_changes(Cursor* c) {
	return c->changes();
}

void free_cursor(Cursor* c) {
	delete c;
}

}