#ifndef LIBORM_CONNECTION_CONNECTION_C_H
#define LIBORM_CONNECTION_CONNECTION_C_H

#ifndef __cplusplus
typedef struct Connection Connection;
#endif

#ifdef __cplusplus
extern "C" {
#endif

__attribute__ ((warn_unused_result)) struct connection_result connection_execute_many(Connection* conn, const char* stmt, void*);
__attribute__ ((warn_unused_result)) struct connection_result connection_execute(Connection* conn, const char* stmt);
__attribute__ ((warn_unused_result)) const char* connection_error_message(Connection* conn);
__attribute__ ((warn_unused_result)) unsigned connection_changes(Connection* conn);
void free_connection(Connection* conn);

#ifdef __cplusplus
}
#endif

#endif

