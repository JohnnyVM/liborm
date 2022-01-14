#ifndef LIBORM_DRIVER_ORACLE_CURSORS_H
#define LIBORM_DRIVER_ORACLE_CURSORS_H

#include "inner_driver_oracle.h"
#include "connection/connection.h"
#include "driver/oracle/connection_data.h"
#include "oracle_types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct resource_ora_cursor{
    conn_state (*prepare)(struct oracle_connection_data*, const char*);
    struct connection_result (*execute)(struct oracle_connection_data*);
    conn_state (*open)(struct oracle_connection_data*, unsigned);
    conn_state (*fetch)(struct oracle_connection_data*, unsigned*);
    conn_state (*close)(struct oracle_connection_data*);
};

#define _DECLARE_ORA_CURSOR_FUNC(ID) \
conn_state driver_ora_cursor_close_##ID(struct oracle_connection_data*); \
conn_state driver_ora_fetch_##ID(struct oracle_connection_data*, unsigned*); \
conn_state driver_ora_cursor_open_##ID(struct oracle_connection_data*, unsigned); \
struct connection_result driver_ora_execute_##ID(struct oracle_connection_data*); \
conn_state driver_ora_prepare_##ID(struct oracle_connection_data*, const char*)
_DECLARE_ORA_CURSOR_FUNC(0);
_DECLARE_ORA_CURSOR_FUNC(1);

#define INIT_ORA_CURSOR(ID) \
{ .prepare = &driver_ora_prepare_##ID,\
  .execute = &driver_ora_execute_##ID, \
  .open = &driver_ora_cursor_open_##ID, \
  .fetch = &driver_ora_fetch_##ID, \
  .close = &driver_ora_cursor_close_##ID \
}

#ifdef __cplusplus
}
#endif

#endif