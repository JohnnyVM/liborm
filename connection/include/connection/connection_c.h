#ifndef LIBORM_CONNECTION_CONNECTION_C_H
#define LIBORM_CONNECTION_CONNECTION_C_H

#ifndef __cplusplus
typedef struct Connection Connection;
#endif

#ifdef __cplusplus
extern "C" {
#endif

__attribute__ ((warn_unused_result)) struct connection_result connection_execute_many(Connection* const conn, const char* const stmt, void*);
__attribute__ ((warn_unused_result)) struct connection_result connection_execute(Connection* const conn, const char* const stmt);
__attribute__ ((warn_unused_result)) conn_state connection_close(Connection* const conn);
__attribute__ ((warn_unused_result)) conn_state connection_begin(Connection* const conn);
__attribute__ ((warn_unused_result)) conn_state connection_commit(Connection* const conn);
__attribute__ ((warn_unused_result)) conn_state connection_rollback(Connection* const conn);
__attribute__ ((warn_unused_result)) const char* connection_error_message(Connection* const conn);
__attribute__ ((warn_unused_result)) unsigned connection_changes(Connection* const conn);
void free_connection(Connection* const conn);

#ifdef __cplusplus
}
#endif

#endif

