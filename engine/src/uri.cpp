#include <string>
#include <utility>
#include <stdexcept>

#include "engine/uri.hpp"

namespace engine {

/**
 * \brief parse a RFC??? uri of type dialect(+driver)://(user:password@)host|ip(:port)(/resource) into struct database_uri
 * \todo refactor to REGEX
 */
engine::RFC1738 RFC1738::parse(std::string uri) {
	struct RFC1738 out;

	std::size_t splitter = uri.find("://");
	if(splitter == std::string::npos) {
		throw std::invalid_argument("Invalid URI");
	}

	// dialect(+driver)?
	std::size_t driver_pos = uri.substr(0, splitter).find("+");
	if(driver_pos == std::string::npos) {
		driver_pos = splitter;
	}
	out.dialect = uri.substr(0, driver_pos);
	out.driver = out.dialect;
	if(driver_pos != splitter) {
		out.driver = uri.substr(driver_pos+1, splitter - driver_pos - 1);
	}
	uri = uri.substr(splitter+3, std::string::npos);

	// user:password
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

}
