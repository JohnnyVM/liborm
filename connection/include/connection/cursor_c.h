#ifndef LIBORM_CONNECTION_CURSOR_C_H
#define LIBORM_CONNECTION_CURSOR_C_H

#include "connection/types.h"

#ifndef __cplusplus
typedef struct Cursor Cursor;
#endif

#ifdef __cplusplus
extern "C" {
#endif

__attribute__ ((warn_unused_result)) conn_state cursor_open(Cursor* c);
__attribute__ ((warn_unused_result)) conn_state cursor_close(Cursor* c);
void free_cursor(Cursor* c);

__attribute__ ((warn_unused_result)) unsigned cursor_nfields(Cursor *c);
__attribute__ ((warn_unused_result)) unsigned cursor_ntuples(Cursor *c);
__attribute__ ((warn_unused_result)) unsigned cursor_changes(Cursor *c);

#ifdef __cplusplus
}
#endif

#endif
