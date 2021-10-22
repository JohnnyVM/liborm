#include <string>
#include <memory>

#include "schema_element.hpp"
#include "table.hpp"
#include "column.hpp"
#include "select.hpp"
#include "query.hpp"

orm::Select::operator const std::string() {
	size_t i;
	std::string os = (std::string)"select ";

	for(i=0; i < object->c.size(); i++) {
		os += (std::string)(i ? "," : "") + object->name + "." + object->c[i]->name;
	}

	os += (std::string)" from " + object->name;

	// TODO where

	return os;
}
