#ifndef LIBORM_DRIVER_ORACLE_CURSOR_HPP
#define LIBORM_DRIVER_ORACLE_CURSOR_HPP

#include <vector>
#include <memory>

#include "connection/connection.h"
#include "driver/oracle/connection.hpp"
#include "inner_driver_oracle.h"
#include "connection_data.h"
#include "type/engine.hpp"

using PCursor = Cursor;

namespace driver::oracle {

/** A Cursor that is representing state from a DBAPI cursor.
 *	Its in charge of handle the memory used
 * \warning The ORACLE DBAPI is designed in way taht the cursor are global variables at file unit
 * this api only provide a cursor, any THREAD aplication have to be designed VERY carefully 
 * around that limitation, or think how remove that
 * */
class Cursor final : public PCursor {
	friend class driver::oracle::Connection;
	public:

	~Cursor();
	Cursor(struct oracle_connection_data arg_data);
	Cursor& operator=(const Cursor& arg);
	[[nodiscard]] conn_state close(void) override final;
	[[nodiscard]] conn_state fetch(void) override final;
	[[nodiscard]] unsigned nfields(void) override final {return _nfields;};
	[[nodiscard]] unsigned nrows(void) override final {return _ntuples;};
	[[nodiscard]] unsigned changes(void) override final {return _changes;};
	[[nodiscard]] bool is_open(void) override final {return _is_open;}
	[[nodiscard]] PCursor* clone_c(void) override final;
	protected:
	[[nodiscard]] conn_state open(void) override final;
	private:
	std::vector<std::unique_ptr<TypeEngine> > _values;
	struct oracle_connection_data conn;
	unsigned _nfields;
	unsigned _ntuples;
	unsigned _changes;
	bool _is_open;
};

}

#endif

