#ifndef LIBORM_ENGINE_H
#define LIBORM_ENGINE_H

#include "connection.h"

#ifndef __cplusplus

typedef struct Engine Engine;

#else

#include <string>
#include <vector>
#include <memory>

#include "type/factory.hpp"

class Engine {
	public:
	Engine(Engine&) = delete;
	void operator=(const Engine&) = delete;
	Engine(const char* uri);
	Connection* connect();
	int foo() { return 1; }

	const std::string dialect;
	const std::string driver;
	const std::string user;
	const std::string password;
	const std::string host;
	const int port = 0;
	const std::string resource;

	std::unique_ptr<orm::TypeFactory> typeFactory;

	private:
	struct database_uri_definition {
		std::string dialect;
		std::string driver;
		std::string user;
		std::string password;
		std::string host;
		int port;
		std::string resource;
	};
	/// \todo do this public
	Engine(struct database_uri_definition args);
	static struct database_uri_definition parse_uri(std::string uri);
	// todo clean connections if engine die
};

#endif

#ifdef __cplusplus
extern "C" {
#endif

/** \brief create a database connection factory */
Engine* create_engine(const char* uri);

/** \brief free the engine connection */
void free_engine(Engine* engine);

/** \brief connect to the data base
 *
 * The purpose of this class is have a control over how
 * the connections are created, but in this case is a bit unnecesary
 * If fail launch exception
 */
Connection* engine_connect(Engine* engine);

#ifdef __cplusplus
}
#endif

#endif
