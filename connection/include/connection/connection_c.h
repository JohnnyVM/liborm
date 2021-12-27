#ifndef LIBORM_CONNECTION_CONNECTION_C_H
#define LIBORM_CONNECTION_CONNECTION_C_H

#ifndef __cplusplus
typedef struct Connection Connection;
#endif

#ifdef __cplusplus
extern "C" {
#endif

[[nodiscard]] struct connection_state connection_execute_many(Connection* conn, const char* stmt, void*);
[[nodiscard]] struct connection_state connection_execute(Connection* conn, const char* stmt);
void free_connection(Connection* conn);

#ifdef __cplusplus
}
#endif

#endif
