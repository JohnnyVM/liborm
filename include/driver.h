#ifndef LIBORM_DRIVER_H
#define LIBORM_DRIVER_H

#include "status.h"

#ifdef __cplusplus
extern "C"
{
	namespace orm {
#endif


/** \brief vtable of operations that have to be fullfilled to be interoperable */
struct orm_driver {
	struct orm_status (*commit)(void* conn);
	struct orm_status (*rollback)(void* conn);
	struct orm_status (*execute)(void* conn, const char*stmt, void*params);
};

#ifdef __cplusplus
	}
}
#endif

#endif

