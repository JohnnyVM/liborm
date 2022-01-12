#ifndef LIBORM_CONNECTION_CURSOR_HPP
#define LIBORM_CONNECTION_CURSOR_HPP

#include <memory>
#include <vector>
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
	[[nodiscard]] virtual Cursor* clone_c(void) const = 0;
	[[nodiscard]] virtual conn_state open(void) = 0;
	[[nodiscard]] virtual conn_state close(void) = 0;
	[[nodiscard]] virtual conn_state fetch(void) = 0; /**< fetch the default quantity determined by the driver */
	[[nodiscard]] virtual unsigned nfields(void) const = 0;
	[[nodiscard]] virtual unsigned nrows(void) const = 0;
	[[nodiscard]] virtual unsigned changes(void) const = 0;
	[[nodiscard]] virtual bool is_open(void) const = 0;
	[[nodiscard]] const std::string& name(unsigned n) const; /**< return the name of the column at n position, empty if out of range*/
	[[nodiscard]] int number(const std::string&) const; /**< return the number of the column of name, -1 if out of range */
	[[nodiscard]] TypeEngine* getValue(unsigned row, unsigned column) const;

	protected:
	std::vector<std::string> _names;
	/// \todo In pure C++ this should be public and defined at Cursor level, but for that i need a Row class
	[[nodiscard]] virtual TypeEngine* _getValue (unsigned row, unsigned column) const = 0;
};

#endif
