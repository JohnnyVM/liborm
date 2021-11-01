#ifndef LIBORM_SQL_DATATYPE_H
#define LIBORM_SQL_DATATYPE_H

/**
 * \brief Define a C <=> SQL datatype interface
 * keep the necesary information about type for comunicate with the engine
 */

#include <stdlib.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
	namespace orm {
#endif

enum sql_datatype {
	INTEGER = 1,
	VARCHAR,
	BOOL,
	//...
};

#ifdef __cplusplus
	}
}
#endif

#endif

