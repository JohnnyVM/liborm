#ifndef LIBORM_ENGINE_URI_HPP
#define LIBORM_ENGINE_URI_HPP

#include <string>

namespace engine {

// These URLs (try) follow RFC-1738
struct RFC1738 {
	std::string dialect = "";
	std::string driver = "";
	std::string user = "";
	std::string password = "";
	std::string host = "";
	int port = 0;
	std::string resource = "";

	RFC1738() = default;
	RFC1738(const RFC1738& arg) :
		dialect(arg.dialect),
		driver(arg.driver),
		user(arg.user),
		password(arg.password),
		host(arg.host),
		port(arg.port),
		resource(arg.resource){}
	RFC1738(const char* arg) : RFC1738((std::string)arg) {}
	RFC1738(const std::string& arg) : RFC1738(parse(arg)) {}
	static RFC1738 parse(std::string uri);
};

}

#endif
