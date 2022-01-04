#ifndef LIBORM_DRIVER_ORACLE_CURSOR_HPP
#define LIBORM_DRIVER_ORACLE_CURSOR_HPP

#include <vector>
#include <memory>
#include <mutex>

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
 * around that limitation, or think how remove that, by default the class block when lock and unlock the cursor
 * */
class Cursor final : public PCursor {
	friend class driver::oracle::Connection;
	public:
	~Cursor();
	Cursor(struct oracle_connection_data arg_data);
	Cursor& operator=(const Cursor& arg);
	[[nodiscard]] conn_state close(void) override;
	[[nodiscard]] conn_state fetch(void) override;
	[[nodiscard]] unsigned nfields(void) override {return _nfields;};
	[[nodiscard]] unsigned nrows(void) override {return _ntuples;};
	[[nodiscard]] unsigned changes(void) override {return _changes;};
	[[nodiscard]] bool is_open(void) override {return _is_open;}
	[[nodiscard]] orm::TypeEngine* _getValue(unsigned row, unsigned column);
	[[nodiscard]] PCursor* clone_c(void) override;
	protected:
	[[nodiscard]] conn_state open(void) override;
	private:
	void open_cursor(void);
	void close_cursor(void);
	std::vector<std::shared_ptr<orm::TypeEngine>> _values;
	std::vector<std::string> names;
	struct oracle_connection_data conn;
	unsigned _nfields;
	unsigned _ntuples;
	unsigned _changes;
	bool _is_open;
	inline static std::mutex m;
	std::once_flag open_cursor_flag, close_cursor_flag;
};

}

#endif

