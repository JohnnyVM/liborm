#include <string>
#include <memory>
#include <cassert>

#include "engine/engine.h"

// Lets keep all dirty work in one function
#ifdef ORACLE
#include "driver/oracle/engine.hpp"
#endif

#ifdef POSTGRES
#include "driver/postgres/engine.hpp"
#endif

extern "C" {

Engine* create_engine(const char* uri_arg) {
	engine::RFC1738 uri{uri_arg};
	Engine* engine = nullptr;

	#ifdef ORACLE
	if(uri.driver == "oracle") {
		engine = new driver::oracle::Engine(uri);
		return engine;
	}
	#endif

	#ifdef POSTGRES
	if(uri.driver == "postgres") {
		engine = new driver::postgres::Engine(uri);
		return engine;
	}
	#endif

	assert(!"Driver not known");

	return engine;
}

}
