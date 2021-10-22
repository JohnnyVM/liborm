#ifndef LIBORM_ENGINE_H
#define LIBORM_ENGINE_H

#include <string>

namespace orm {

struct database_uri {
	std::string dialect;
	std::string driver;
	std::string username;
	std::string password;
	std::string host;
	int port;
	std::string database;
};

/* Base class */
class Engine {
	public:
	Engine() = default;
	Engine(const Engine&) = delete;
	virtual ~Engine() = default;
	Engine& operator=(const Engine&) = delete;

	struct database_uri params;
	Engine(struct database_uri uri) : params(uri) {}
};


/**
 * \brief create The create_engine() function produces an Engine object based on a URL.
 * the url is dialect+driver://username:password@host:port/database, to be honest, we dont support the driver
 */
//Engine create_engine(const std::string& database_url);

}

#endif
