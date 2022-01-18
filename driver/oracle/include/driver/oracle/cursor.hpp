#ifndef LIBORM_DRIVER_ORACLE_CURSOR_HPP
#define LIBORM_DRIVER_ORACLE_CURSOR_HPP

#include <vector>
#include <memory>

#include "connection/connection.h"
#include "driver/oracle/connection.hpp"
#include "inner_driver_oracle.h"
#include "connection_data.h"
#include "liborm/type/engine.h"

using PCursor = Cursor;
using resource_ora_cursor = struct resource_ora_cursor;

namespace driver::oracle {

/** A Cursor that is representing state from a DBAPI cursor.
 *	Its in charge of handle the memory used
 * \warning The ORACLE DBAPI is designed in way taht the cursor are global variables at file unit
 * this api only provide a cursor, any THREAD aplication have to be designed VERY carefully 
 * around that limitation, or think how remove that, by default the class block when lock and unlock the cursor
 * \warning the thread context of the cursor is a variably carried by the connection, you cannoy free the connection and use the cursor
 * */
class Cursor final : public PCursor {
	friend class driver::oracle::Connection;
	public:
	~Cursor();
	Cursor(struct oracle_connection_data arg_data, std::shared_ptr<resource_ora_cursor> cursor);
	Cursor& operator=(const Cursor& arg);
	[[nodiscard]] conn_state close(void) override;
	[[nodiscard]] conn_state fetch(void) override;
	[[nodiscard]] unsigned nfields(void) const override { return _nfields; }
	[[nodiscard]] unsigned nrows(void) const override { return _ntuples; }
	[[nodiscard]] unsigned changes(void) const override { return _changes; }
	[[nodiscard]] bool is_open(void) const override { return cursor.use_count() > 0; }
	[[nodiscard]] TypeEngine* _getValue(unsigned row, unsigned column) const override;
	protected:
	[[nodiscard]] conn_state open(void) override;
	private:
	std::vector<std::shared_ptr<TypeEngine>> _values;
	std::shared_ptr<struct resource_ora_cursor> cursor;
	conn_state open_cursor(void);
	void close_cursor(void);
	struct oracle_connection_data conn;
	unsigned _nfields;
	unsigned _ntuples;
	unsigned _changes;
	std::once_flag open_cursor_flag, close_cursor_flag;
};

}

#endif

