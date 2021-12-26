#include <string>
#include <memory>

#include "engine.h"

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
	if(uri->driver == "oracle") {
		engine = new engine::Oracle(uri, std::make_shared<driver::oracle::TypeEngine>());
	}
	#endif

	#ifdef POSTGRES
	if(uri->driver == "postgres") {
		engine = new engine::Postgres(uri, std::make_shared<driver::oracle::TypeEngine>());
	}
	#endif

	if(engine == nullptr){
		throw std::invalid_argument((std::string)"Driver " + uri.driver + " not know");
	}

	return engine;
}

}
