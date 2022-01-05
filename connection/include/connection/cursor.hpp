#ifndef LIBORM_CONNECTION_CURSOR_HPP
#define LIBORM_CONNECTION_CURSOR_HPP

#include <memory>
#include <string>

#include "type/types.hpp"
#include "connection/types.h"

/** A Cursor that is representing state from a DBAPI cursor.
 *	Its in charge of handle the memory used
 * */
class Cursor {
	public:
	virtual ~Cursor() = default;
	Cursor& operator=(const Cursor&) = delete;
	[[nodiscard]] virtual Cursor* clone_c(void) = 0;
	[[nodiscard]] virtual conn_state fetch(void) = 0; /**< fetch the default quantity determined by the driver */
	[[nodiscard]] virtual unsigned nfields(void) = 0;
	[[nodiscard]] virtual unsigned nrows(void) = 0;
	[[nodiscard]] virtual unsigned changes(void) = 0;
	[[nodiscard]] virtual bool is_open(void) = 0;
	[[nodiscard]] virtual conn_state open(void) = 0;
	[[nodiscard]] virtual conn_state close(void) = 0;
	//[[nodiscard]] virtual std::string name(unsigned n) = 0; /**< return the name of the column at n position*/
	[[nodiscard]] TypeEngine* getValue(unsigned row, unsigned column);
	//[[nodiscard]] virtual conn_state getValue(void) = 0;
	protected:
	[[nodiscard]] virtual TypeEngine* _getValue (unsigned row, unsigned column) = 0;
};

#endif
