#include "connection.h"

struct connection_state cursor_open(Cursor* c) {
	return c->open();
}

struct connection_state cursor_close(Cursor* c) {
	return c->close();
}

unsigned cursor_ntuples(Cursor* c) {
	return c->nrows();
}

unsigned cursor_nfields(Cursor* c) {
	return c->nfields();
}

unsigned cursor_changes(Cursor* c) {
	return c->changes();
}

void free_cursor(Cursor* c) {
	c->close();
	delete c;
}

