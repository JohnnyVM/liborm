#ifndef LIBORM_CONNECTION_CONNECTION_C_H
#define LIBORM_CONNECTION_CONNECTION_C_H

#include "connection/statement.h"

#ifndef __cplusplus
typedef struct Connection Connection;
#endif

#ifdef __cplusplus
extern "C" {
#endif

__attribute__((warn_unused_result)) struct connection_result connection_execute(Connection* conn, const char* const stmt);
__attribute__((warn_unused_result)) conn_state connection_close(Connection* conn);
__attribute__((warn_unused_result)) conn_state connection_begin(Connection* conn);
__attribute__((warn_unused_result)) conn_state connection_commit(Connection* conn);
__attribute__((warn_unused_result)) conn_state connection_rollback(Connection* conn);

__attribute__((warn_unused_result)) Statement* connection_prepare(const char* stmt);
__attribute__((warn_unused_result)) struct connection_result connection_step(Connection* conn, Statement* stmt);

__attribute__((warn_unused_result)) const char* connection_error_message(Connection* const conn);
__attribute__((warn_unused_result)) unsigned connection_changes(Connection* const conn);
void free_connection(Connection* conn);
void free_statement(Statement*);

#ifdef __cplusplus
}
#endif

#endif

