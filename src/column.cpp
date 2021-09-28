#include <iterator>
#include <memory>
#include <string>

#include "column.hpp"

orm::Column::operator const std::string() {
	std::string os = name + " " + (std::string)*type;

	if(primary_key) {
		os += (std::string)" " + "primary key";
	}

	if(!nullable) {
		os += (std::string)" " + "not null";
	}

	if(default_value) {
		/// todo
	}

	return os;
}

