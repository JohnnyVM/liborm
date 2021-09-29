#include <string>
#include <memory>

#include "schema_element.hpp"
#include "table.hpp"
#include "column.hpp"
#include "delete.hpp"

orm::Delete::operator const std::string() {
	std::string os = (std::string)"delete ";

	os += (std::string)"from " + object->name;

	// TODO where

	return os;
}

