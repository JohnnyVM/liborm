#ifndef LIBORM_DRIVER_SQLITE_ERROR_MESSAGE_H
#define LIBORM_DRIVER_SQLITE_ERROR_MESSAGE_H

#include "database_params.h"
#include "libdict/dict.h"
#include "status.h"

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef HIDDEN_VISIBILITY
const char* error_message(struct sqlite_connection* db);
#endif

const char* driver_sqlite_error_message(void* conn);

#ifdef __cplusplus
}
#endif

#endif

