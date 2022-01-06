#ifndef LIBORM_CONNECTION_CURSOR_C_H
#define LIBORM_CONNECTION_CURSOR_C_H

#include "connection/types.h"
#include "type/engine.h"

#ifndef __cplusplus
typedef struct Cursor Cursor;
#endif

#ifdef __cplusplus
extern "C" {
#endif

__attribute__ ((warn_unused_result)) conn_state cursor_open(Cursor* const c);
__attribute__ ((warn_unused_result)) conn_state cursor_close(Cursor* const c);
__attribute__ ((warn_unused_result)) conn_state cursor_fetch(Cursor* const c);
void free_cursor(Cursor* const c);

__attribute__ ((warn_unused_result)) unsigned cursor_nfields(Cursor* const c);
__attribute__ ((warn_unused_result)) unsigned cursor_nrows(Cursor* const c);
__attribute__ ((warn_unused_result)) unsigned cursor_changes(Cursor* const c);
__attribute__ ((warn_unused_result)) TypeEngine* cursor_getValue(Cursor* const c, unsigned row, unsigned column);

#ifdef __cplusplus
}
#endif

#endif
