#include <string>
#include <memory>
#include <stdexcept>      // std::invalid_argument

#include "engine.h"
#include "connection.h"
#include "type/factory.hpp"
#ifdef DRIVER_ORACLE
#include "driver/oracle.hpp"
#endif
#ifdef DRIVER_POSTGRES
#include "driver/postgres.hpp"
#endif

/**
 * \brief parse a RFC??? uri of type dialect(+driver)://(user:password@)host|ip(:port)(/resource) into struct database_uri
 * \todo refactor to REGEX
 */
Engine::database_uri_definition Engine::parse_uri(std::string uri) {
	struct database_uri_definition out = {
		.dialect = "",
		.driver = "",
		.user = "",
		.password = "",
		.host = "",
		.port = 0,
		.resource = ""
	};

	std::size_t splitter = uri.find("://");
	if(splitter == std::string::npos) {
		throw std::invalid_argument("Invalid URI");
	}

	// dialect(+driver)?
	std::size_t driver_pos = uri.substr(0, splitter).find("+");
	out.dialect = uri.substr(0, driver_pos);
	if(driver_pos != std::string::npos) {
		out.driver = uri.substr(driver_pos+1, splitter - driver_pos - 1);
	}
	uri = uri.substr(splitter+3, std::string::npos);

	std::size_t end_credentials = uri.find("@");
	if(end_credentials != std::string::npos) {
		std::string credentials = uri.substr(0, end_credentials);
		std::size_t splitcre = uri.find(":");
		if(splitcre != std::string::npos){
			out.password = credentials.substr(splitcre+1, std::string::npos);
			credentials = credentials.substr(0, splitcre);
		}
		out.user = credentials;
		uri = uri.substr(end_credentials+1, std::string::npos);
	}

	// ://(host)(:port)?(/resource)
	std::size_t resource_pos = uri.find("/");
	if(resource_pos != std::string::npos){
		out.resource = uri.substr(resource_pos+1, std::string::npos);
		uri = uri.substr(0, resource_pos);
	}

	std::size_t port_pos = uri.find(":");
	if(port_pos != std::string::npos){
		out.port = std::stoi(uri.substr(port_pos+1, std::string::npos));
		uri = uri.substr(0, port_pos);
	}

	out.host = uri;

	return out;
}

Engine::Engine(Engine::database_uri_definition args) :
		dialect(args.dialect),
		driver(args.driver),
		user(args.user),
		password(args.password),
		host(args.host),
		port(args.port),
		resource(args.resource) {}

Engine::Engine(const char*__restrict arg_uri) : Engine(parse_uri(arg_uri)) {}

Connection* Engine::connect() {
	Connection* conn = nullptr;

#ifdef DRIVER_ORACLE
	if(this->driver == "oracle") {
		conn = new driver::Oracle(this);
	}
#endif
#ifdef DRIVER_POSTGRES
	if(this->driver == "postgres") {
		//this->
		conn = new driver::Postgres(this);
	}
#endif

	if(conn == nullptr){
		throw std::invalid_argument((std::string)"Driver " + this->driver + " not know");
	}

	struct connection_state state = conn->open();
	if(state.error) {
		// TODO handle error with conn->error_message
		throw std::invalid_argument("Could not connect to database");
	}

	return conn;
}

Engine* create_engine(const char* uri) {
	return new Engine{uri};
}

/** \brief free the engine connection
 * \todo move this inside engine class
 * */
void free_engine(Engine* engine) {
	delete engine;
}

Connection* engine_connect(Engine* engine) {
	return engine->connect();
}
