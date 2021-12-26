#ifndef LIBORM_ENGINE_ENGINE_H
#define LIBORM_ENGINE_ENGINE_H

#include "connection.h"

#ifndef __cplusplus

typedef struct Engine Engine;

#else

#include <string>
#include <memory>

#include "type/factory.hpp"
#include "engine/uri.hpp"

class Connection;

class Engine {
	public:
	Engine(const Engine&) = delete;
	void operator=(const Engine&) = delete;
	Engine(const char* uri);
	[[nodiscard]] virtual Connection* connect() = 0;
	virtual ~Engine() {}

	// This tend to missuse
	std::shared_ptr<const orm::TypeFactory> typeFactory;
	// todo dialect

	// teorically it should pass a class Dialect
	Engine(std::string uri, orm::TypeFactory* arg) :
		typeFactory(arg), params(engine::RFC1738{uri}) {}

	private:
	engine::RFC1738 params;
};

#endif

#ifdef __cplusplus
extern "C" {
#endif

[[nodiscard]] Engine* create_engine(const char* uri);

void free_engine(Engine* engine);

[[nodiscard]] Connection* engine_connect(Engine* engine);

#ifdef __cplusplus
}
#endif

#endif

