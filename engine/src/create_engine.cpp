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

std::unique_ptr<Engine> create_engine(const std::string& uri_arg) {
	engine::RFC1738 uri{uri_arg};
	std::string driver = uri.driver;
	if(uri.driver.empty()) {
		driver = uri.dialect;
	}

	#ifdef ORACLE
	if(driver == "oracle") {
		return std::make_unique<driver::oracle::Engine>(uri);
	}
	#endif

	#ifdef POSTGRES
	if(driver == "postgres") {
		return std::make_unique<driver::postgres::Engine>(uri);
	}
	#endif

	assert(!"Driver not known");

	return nullptr;
}

extern "C" {

Engine* create_engine_p(const char* uri){
	std::shared_ptr<Engine> engine = create_engine((std::string)uri);

	return engine->clone_c();
}

}
