#ifndef DRIVER_SQLITE_CONNECTION_H
#define DRIVER_SQLITE_CONNECTION_H

#include "sqlite3.h"

struct sqlite_connection {
	sqlite3 *database;
};

#endif
