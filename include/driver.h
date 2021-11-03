#ifndef LIBORM_DRIVER_H
#define LIBORM_DRIVER_H

#include "database_params.h"
#include "libarray/array.h"
#include "status.h"

#ifdef __cplusplus
extern "C"
{
	namespace orm {
#endif


/** \brief vtable of operations that have to be fullfilled to be interoperable */
struct driver {
	/* this is the minimun common set of operations */
	/* database operations */
	struct orm_status (*open)(struct database_params* db_params);
	struct orm_status (*close)(void* conn);
	struct orm_status (*commit)(void* conn);
	struct orm_status (*rollback)(void* conn);
	struct orm_status (*execute_many)(void* conn, const char*stmt, struct array *params);
	struct orm_status (*fetch_many)(void*conn);

	/** \todo database structure */
	struct orm_status (*get_columns)(void);
	struct orm_status (*get_table_id)(void);
	struct orm_status (*get_column_definition)(void);
	/* etc */
	const char* (*error_message)(void*); /**< transform a error code in a message database specific */
};

#ifdef __cplusplus
	}
}
#endif

#endif

