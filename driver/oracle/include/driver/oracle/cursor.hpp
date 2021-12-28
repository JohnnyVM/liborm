#ifndef LIBORM_DRIVER_ORACLE_CURSOR_HPP
#define LIBORM_DRIVER_ORACLE_CURSOR_HPP

#include <vector>
#include <memory>

#include "connection.h"
#include "driver/oracle/connection.hpp"
#include "inner_driver_oracle.h"
#include "connection_data.h"
#include "type/engine.hpp"

using PCursor = Cursor;

namespace driver {
class Oracle;
}

namespace driver::oracle {

/** A Cursor that is representing state from a DBAPI cursor.
 *	Its in charge of handle the memory used
 * */
class Cursor : public PCursor {
	friend class driver::oracle::Connection;
	public:
	//virtual void fetch(void) = 0; // fetch the default quantity determined by the driver
	//virtual unsigned fields(void) = 0;
	~Cursor();
	Cursor(struct oracle_connection_data arg_data);
	[[nodiscard]] conn_error close(void) override;
	[[nodiscard]] conn_error fetch(void) override;
	[[nodiscard]] unsigned nfields() override {return _nfields;};
	[[nodiscard]] unsigned nrows() override {return _ntuples;};
	[[nodiscard]] unsigned changes() override {return _changes;};
	[[nodiscard]] bool is_open() override {return _is_open;}
	protected:
	[[nodiscard]] conn_error open(void) override;
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

