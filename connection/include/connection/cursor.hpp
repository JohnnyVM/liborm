#ifndef LIBORM_CONNECTION_CURSOR_HPP
#define LIBORM_CONNECTION_CURSOR_HPP

#include "connection/types.h"

/** A Cursor that is representing state from a DBAPI cursor.
 *	Its in charge of handle the memory used
 * */
class Cursor {
	public:
	virtual ~Cursor() {}
	Cursor(const Cursor&) = delete;
	void operator=(const Cursor&) = delete;
	virtual struct connection_state fetch(void) = 0; /**< fetch the default quantity determined by the driver */
	virtual unsigned nfields(void) = 0;
	virtual unsigned nrows(void) = 0;
	virtual unsigned changes(void) = 0;
	virtual bool is_open(void) = 0;
	virtual struct connection_state open(void) = 0;
	virtual struct connection_state close(void) = 0;
};

#endif
