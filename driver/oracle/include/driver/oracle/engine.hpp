#ifndef LIBORM_DRIVER_ORACLE_ENGINE_H
#define LIBORM_DRIVER_ORACLE_ENGINE_H

#include <string>
#include <memory>

#include "connection/connection.h"
#include "engine/engine.h"
#include "driver/oracle/connection.hpp"

using PEngine = Engine;
using PConnection = Connection;

namespace driver::oracle {

/** A Cursor that is representing state from a DBAPI cursor.
 *	Its in charge of handle the memory used
 * */
class Engine final : public PEngine {
	public:
	~Engine() override {}
	Engine(const std::string& uri) : PEngine(uri) {}
	Engine(const engine::RFC1738& uri) : PEngine(uri) {}
	Engine& operator=(const Engine& arg) { params = arg.params; return *this; } 
	[[nodiscard]] std::unique_ptr<PConnection> connect(void) override; /**< returna open connection to the dbapi */
	[[nodiscard]] PEngine* clone_c(void) override; /**< return open connection to the dbapi */

	private:
	struct oracle_connection_data params_to_conn();
};

}

#endif


