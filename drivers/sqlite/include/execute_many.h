#ifndef LIBORM_DRIVER_SQLITE_EXECUTE_MANY_H
#define LIBORM_DRIVER_SQLITE_EXECUTE_MANY_H

#include "database_params.h"
#include "libarray/array.h"
#include "status.h"
#include "common.h"
#include "visibility.h"

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef HIDDEN_VISIBILITY
NO_DISCARD struct orm_status execute_many(struct sqlite_connection* conn, const char* stmt, struct array* params);
#endif

NO_DISCARD struct orm_status driver_sqlite_execute_many(void* conn, const char* stmt, struct array* params);

#ifdef __cplusplus
}
#endif

#endif

