#ifndef LIBORM_ENGINE_ENGINE_H
#define LIBORM_ENGINE_ENGINE_H

#include "connection.h"

#ifndef __cplusplus

typedef struct Engine Engine;

#else

#include <string>
#include <memory>

#include "engine/uri.hpp"

class Connection;

class Engine {
	public:
	Engine(const Engine&) = delete;
	void operator=(const Engine&) = delete;
	virtual ~Engine() {}
	Engine(const char* uri) : Engine((std::string)uri) {}
	// teorically it should pass a class Dialect (see the documentation)
	Engine(std::string uri) : params(engine::RFC1738{uri}) {}

	[[nodiscard]] virtual Connection* connect() = 0; /**< returna open connection to the dbapi */

	protected:
	engine::RFC1738 params;
};

#endif

#ifdef __cplusplus
extern "C" {
#endif

Engine* create_engine(const char* uri);

void free_engine(Engine* engine);

Connection* engine_connect(Engine* engine);

#ifdef __cplusplus
}
#endif

#endif

