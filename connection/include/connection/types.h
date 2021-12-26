#ifndef LIBORM_CONNECTION_TYPES_H
#define LIBORM_CONNECTION_TYPES_H

enum connection_error {
	NO_CONNECTION_ERROR = 0, /**< no error */
	DATABASE_ERROR, /**< DBAPI error */
};

#define conn_error_t enum connection_error

#endif
