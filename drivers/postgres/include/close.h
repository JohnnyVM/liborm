#ifndef LIBORM_DRIVER_SQLITE_CLOSE_H
#define LIBORM_DRIVER_SQLITE_CLOSE_H

#include "database_params.h"
#include "libdict/dict.h"
#include "status.h"
#include "common.h"
#include "connection.h"

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef HIDDEN_VISIBILITY
NO_DISCARD struct orm_status close(struct sqlite_connection* conn);
#endif

NO_DISCARD struct orm_status driver_sqlite_close(void* conn);

#ifdef __cplusplus
}
#endif

#endif

