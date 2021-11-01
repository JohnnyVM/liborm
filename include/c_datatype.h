#ifndef LIBORM_C_DATATYPE_H
#define LIBORM_C_DATATYPE_H

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

enum c_type {
	INTEGER = 1,
	CHARACTER,
	CHAR,
	BOOL,
	FLOAT,
	DOUBLE,
	//...
};

/**
 * \brief struct that keep the necesary info about c type pased as param
 */
struct c_datatype {
	enum c_type type;
	size_t length;
	size_t octet_length;
	bool null_value;
	// locale
	unsigned char data[];
};

#ifdef __cplusplus
	}
}
#endif

#endif

