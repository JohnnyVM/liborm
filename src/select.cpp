#include <string>
#include <memory>

#include "schema_element.hpp"
#include "table.hpp"
#include "column.hpp"
#include "select.hpp"

orm::Select::operator const std::string() {
	size_t i;
	std::string os = (std::string)"select ";

	for(i=0; i < object->columns.size() - 1; i++) {
		os += object->name + "." + object->columns[i]->name + ",";
	}
	os += object->name + "." + object->columns[i+1]->name; // avoid trailing coma

	os += (std::string)"from " + object->name;

	// TODO where

	return os;
}
