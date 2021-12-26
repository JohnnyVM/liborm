#ifndef LIBORM_CONNECTION_H
#define LIBORM_CONNECTION_H

#include "connection/types.h"

#ifdef __cplusplus

#include "connection/cursor.hpp"
#include "connection/connection.hpp"

#else

#include "connection/state.h"
#include "connection/cursor_c.h"
#include "connection/connection_c.h"

#endif

#endif
