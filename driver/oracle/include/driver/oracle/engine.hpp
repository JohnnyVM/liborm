#ifndef LIBORM_DRIVER_ORACLE_ENGINE_H
#define LIBORM_DRIVER_ORACLE_ENGINE_H

#include <string>

#include "connection.h"

using PEngine = Engine;

namespace driver::oracle {

/** A Cursor that is representing state from a DBAPI cursor.
 *	Its in charge of handle the memory used
 * */
class Engine : public PEngine {
	Engine(const std::string& uri) : PEngine(uri) {}
	[[nodiscard]] Connection* connect() override; /**< returna open connection to the dbapi */

	private:
	struct oracle_connection_data params_to_conn();
};

}

#endif


