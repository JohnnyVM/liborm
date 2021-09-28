#include <string>
#include <memory>

#include "schema_element.hpp"
#include "table.hpp"
#include "column.hpp"
#include "select.hpp"

orm::Select::operator const std::string() {
	size_t i;
	std::string os = (std::string)"select ";

	for(i=0; i < selectable->columns.size() - 1; i++) {
		os += selectable->name + "." + selectable->columns[i]->name + ",";
	}
	os += selectable->name + "." + selectable->columns[i+1]->name; // avoid trailing coma

	os += (std::string)"from " + selectable->name;

	// TODO where

	return os;
}
