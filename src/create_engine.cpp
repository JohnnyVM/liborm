#include <cstdio>
#include <stdexcept>
#include <string>
#include <regex>
#include <cassert>

#include "engine.hpp"

/*static struct orm::database_uri parse_database_uri(const std::string& database_uri){
	struct orm::database_uri result;

	std::smatch base_match;
	std::regex base_regex("(\\S+)://((\\S+):(\\S+)@(\\S+)(:(\\d+))?)?/(\\S+)");

	if(!std::regex_match(database_uri, base_match, base_regex)) {
		throw std::invalid_argument("Invalid database URI");
	}

	if(base_match.size() == 6) {
		result.dialect = base_match[0].str();
		result.username = base_match[1].str();
		result.password = base_match[2].str();
		result.host = base_match[3].str();
		result.port = stoi(base_match[4].str());
		result.database = base_match[5].str();
	}

	if(base_match.size() == 2) {
		result.dialect = base_match[0].str();
		result.database = base_match[1].str();
	}

	return result;
}*/

/*orm::Engine orm::create_engine(const std::string& database_url) {
	orm::Engine engine;
	struct orm::database_uri db_uri = parse_database_uri(database_url);

	if(db_uri.dialect == (std::string)"postgres") {

	}

	if(db_uri.dialect == (std::string)"sqlite") {

	}

	if(db_uri.dialect == (std::string)"oracle") {

	}

	assert(0);
}*/
