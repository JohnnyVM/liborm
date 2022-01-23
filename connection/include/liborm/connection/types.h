#ifndef LIBORM_CONNECTION_TYPES_H
#define LIBORM_CONNECTION_TYPES_H

enum connection_state {
	SQL_DONE = 0, /**< no error */
	SQL_ROWS, /**< if ok, connection can be fetched, it doesnt mean some rows have to be returned */
	SQL_MISUSE, /**< Bad use of the API, reopen a closed cursor, fetch closed cursors etc*/
	DATABASE_ERROR, /**< DBAPI error */
	NO_MEMORY, /** ENOMEM equivalence */
	SQL_MAXOPENCURSORS /** */
};

#define conn_state enum connection_state

#endif
