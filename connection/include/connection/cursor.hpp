#ifndef LIBORM_CONNECTION_CURSOR_HPP
#define LIBORM_CONNECTION_CURSOR_HPP

#include <memory>
#include <vector>
#include <string>
#include <cassert>

#include "liborm/type/engine.h"
#include "liborm/connection/types.h"

/** A Cursor that is representing state from a DBAPI cursor.
 *	Its in charge of handle the memory used
 * */
class Cursor {
	public:
	virtual ~Cursor() = default;
	Cursor& operator=(const Cursor&) = delete;
	[[nodiscard]] virtual conn_state open(void) = 0;
	[[nodiscard]] virtual conn_state close(void) = 0;
	[[nodiscard]] virtual conn_state fetch(void) = 0; /**< fetch the default quantity determined by the driver */
	[[nodiscard]] virtual unsigned nfields(void) const = 0;
	[[nodiscard]] virtual unsigned nrows(void) const = 0;
	[[nodiscard]] inline size_t size(unsigned n) const { return _size.at(n); }; /**< Returns the size in bytes of the column associated with the given column number. */
	template<typename T, std::enable_if_t<std::is_convertible<T, std::string>::value || std::is_same<T, std::string>::value, bool> = true>
	[[nodiscard]] inline size_t size(const T& __col) const {
		std::string col = std::string(__col);
		assert(number(col) >= 0);
		return _size.at((unsigned)number(col));
	}
	[[nodiscard]] const std::type_info& type(unsigned n) const { return _type_id.at(n); }; /**< Returns the data type associated with the given column number */
	[[nodiscard]] virtual unsigned changes(void) const = 0;
	[[nodiscard]] virtual bool is_open(void) const = 0;
	[[nodiscard]] const std::string& name(unsigned n) const; /**< return the name of the column at n position, empty if out of range*/
	[[nodiscard]] int number(const std::string&) const; /**< return the number of the column of name, -1 if out of range */
	[[nodiscard]] TypeEngine* getValue(unsigned row, unsigned column) const;
	template<typename T, std::enable_if_t<std::is_convertible<T, std::string>::value || std::is_same<T, std::string>::value, bool> = true>
	[[nodiscard]] inline TypeEngine* getValue(unsigned row, const T& __col) const {
		std::string col = std::string(__col);
		assert(number(col) >= 0);
		return getValue(row, (unsigned)number(col));
	}

	protected:
	std::vector<std::string> _names;
	std::vector<size_t> _size;
	std::vector<std::reference_wrapper<const std::type_info>> _type_id;
	/// \todo In pure C++ this should be public and defined at Cursor level, but for that i need a Row class
	[[nodiscard]] virtual TypeEngine* _getValue (unsigned row, unsigned column) const = 0;
};

#endif
