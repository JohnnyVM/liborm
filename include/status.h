#ifndef LIBORM_STATUS_H
#define LIBORM_STATUS_H

#include "libarray/array.h"

#ifdef __cplusplus
extern "C"
{
	namespace orm {
#endif

/** \brief list of error codes */
enum orm_status_code {
	NO_ERROR = 0,
	UNKNOW_ERROR = 1,
	INVALID_PARAMETERS,
	SQLITE3_ERROR,
};

enum orm_status_type {
	NO_OUTPUT = 1, // orm_status dont have a usefull output in the unnamed union
	RESULT,
	ROW,
	SQLITE3_CONNECTION,
	POSTGRES_CONNECTION,
	ORACLE_CONNECTION,
};

struct orm_status {
	enum orm_status_code error;
	enum orm_status_type type;
	int error_code; /* this is common, when a driver fail with a inner error */
	union {
		struct array* result;
		void* connection;
	};
};

#ifdef __cplusplus
	}
}
#endif

#endif

