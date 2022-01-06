#include <string>
#include <memory>
#include <cassert>

#include "engine/engine.h"
#include "connection/connection.h"

// Lets keep all dirty work in one function
#ifdef ORACLE
#include "driver/oracle/engine.hpp"
#endif

#ifdef POSTGRES
#include "driver/postgres/engine.hpp"
#endif

extern "C" {

/** \brief free the engine connection
 * \todo move this inside engine class
 * */
void free_engine(Engine* const engine) {
	delete engine;
}

Connection* engine_connect(Engine* const engine) {
	std::unique_ptr<Connection>conn = engine->connect();

	return conn->clone_c();
}

}
