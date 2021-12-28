#ifndef LIBORM_CONNECTION_CURSOR_C_H
#define LIBORM_CONNECTION_CURSOR_C_H

#include "connection/types.h"

typedef struct Cursor Cursor;

#ifdef __cplusplus
extern "C" {
#endif

conn_state cursor_open(Cursor* c);
conn_state cursor_close(Cursor* c);
void free_cursor(Cursor* c);

unsigned cursor_nfields(Cursor *c);
unsigned cursor_ntuples(Cursor *c);
unsigned cursor_changes(Cursor *c);

#ifdef __cplusplus
}
#endif

#endif
