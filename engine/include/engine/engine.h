#ifndef LIBORM_ENGINE_ENGINE_H
#define LIBORM_ENGINE_ENGINE_H

#include "connection/connection.h"

#ifndef __cplusplus

typedef struct Engine Engine;

#else

#include <string>
#include <memory>

#include "engine/uri.hpp"

class Connection;

class Engine {
	public:
	Engine(const Engine&) = delete; // avoid object slicing
	Engine& operator=(const Engine&) = delete;
	virtual ~Engine() = default;
	Engine(const char* uri) : Engine((std::string)uri) {}
	// teorically it should pass a class Dialect (see the documentation)
	Engine(const std::string& uri) : Engine(engine::RFC1738{uri}) {}
	Engine(const engine::RFC1738& uri) : params(uri) {}

	[[nodiscard]] virtual std::shared_ptr<Connection> connect() = 0; /**< returna open connection to the dbapi */

	protected:
	engine::RFC1738 params;
};

#endif

#ifdef __cplusplus
extern "C" {
#endif

__attribute__ ((warn_unused_result)) Engine* create_engine(const char* uri);

void free_engine(Engine* engine);

__attribute__ ((warn_unused_result)) Connection* engine_connect(Engine* engine);

#ifdef __cplusplus
}
#endif

#endif

