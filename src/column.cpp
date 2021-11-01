#include <iterator>
#include <memory>
#include <string>

#include "column.hpp"

std::shared_ptr<orm::Column> orm::column(column_params p) {
	return std::make_shared<orm::Column>(p);
}

/*orm::Column::operator const std::string() {
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
}*/

