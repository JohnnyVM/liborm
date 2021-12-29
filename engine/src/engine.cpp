#include "engine/engine.h"
#include "connection/connection.h"

extern "C" {

/** \brief free the engine connection
 * \todo move this inside engine class
 * */
void free_engine(Engine* engine) {
	delete engine;
}

Connection* engine_connect(Engine* engine) {
	return engine->connect();
}

}
