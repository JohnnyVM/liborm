#ifndef LIBORM_DRIVER_ORACLE_CONNECT_H
#define LIBORM_DRIVER_ORACLE_CONNECT_H

#include <assert.h>

#include "connection.h"
#include "driver/oracle/connection_data.h"
#include "oracle_types.h"

#define ORA_NOT_FOUND 100

#if defined(ORA_PROC)
typedef long double _Decimal128;
#endif

#ifdef __cplusplus
#include <decimal/decimal>
using _Decimal128 = std::decimal::decimal128;
#endif

#ifdef __cplusplus
extern "C" {
#endif

struct connection_state driver_ora_connect(struct oracle_connection_data* conn);
struct connection_state driver_ora_commit(struct oracle_connection_data* conn);
struct connection_state driver_ora_close(struct oracle_connection_data* conn);
struct connection_state allocate_descriptor_global(struct oracle_connection_data* dbconn, unsigned char* descriptor);
struct connection_state driver_ora_execute_many(struct oracle_connection_data* dbconn, const char* stmt, void* rows);
struct connection_state driver_ora_cursor_open(struct oracle_connection_data* conn, unsigned fields);
struct connection_state driver_ora_cursor_close(struct oracle_connection_data* conn);
struct connection_state driver_ora_fields_count(struct oracle_connection_data* conn, unsigned* i);
struct connection_state driver_ora_fetch(struct oracle_connection_data* conn, unsigned* changes);
struct connection_state driver_ora_get_descriptor_column(struct oracle_connection_data* conn, unsigned field, struct ora_database_type *result);
_Decimal128 number_to_Decimal128(unsigned char const* number, int size);

#ifdef __cplusplus
}
#endif

#endif
