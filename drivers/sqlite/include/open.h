#ifndef LIBORM_DRIVER_SQLITE_OPEN_H
#define LIBORM_DRIVER_SQLITE_OPEN_H

#include "database_params.h"
#include "libdict/dict.h"
#include "status.h"
#include "common.h"

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef HIDDEN_VISIBILITY
NO_DISCARD struct orm_status open(struct database_params* db_params);
#endif

NO_DISCARD struct orm_status driver_sqlite_open(struct database_params* db_params);

#ifdef __cplusplus
}
#endif

#endif

