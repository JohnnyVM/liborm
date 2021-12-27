#ifndef LIBORM_DRIVER_ORACLE_CURSOR_HPP
#define LIBORM_DRIVER_ORACLE_CURSOR_HPP

#include <vector>
#include <memory>

#include "connection.h"
#include "inner_driver_oracle.h"
#include "connection_data.h"

using PCursor = Cursor;

namespace driver {
class Oracle;
}

namespace driver::oracle {

/** A Cursor that is representing state from a DBAPI cursor.
 *	Its in charge of handle the memory used
 * */
class Cursor : public PCursor {
	friend class driver::Oracle;
	public:
	//virtual void fetch(void) = 0; // fetch the default quantity determined by the driver
	//virtual unsigned fields(void) = 0;
	~Cursor();
	Cursor(struct oracle_connection_data* arg_data);
	struct connection_state open(void) override;
	struct connection_state close(void) override;
	struct connection_state fetch(void) override;
	unsigned nfields() override {return _nfields;};
	unsigned nrows() override {return _ntuples;};
	unsigned changes() override {return _changes;};
	bool is_open() override {return _open;}
	private:
	std::vector<std::unique_ptr<TypeEngine> > _values;
	struct oracle_connection_data* data;
	unsigned _nfields;
	unsigned _ntuples;
	unsigned _changes;
	bool _open;
};

}

#endif

